WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua 游戏"

--游戏状态
GAME_LOG	    =   0           --欢迎画面
GAME_START	    =   1           --游戏已开始
GAME_OVER	    =   2           --游戏已结束

gameStatus      =   GAME_LOG	--游戏状态

mapOffset         =   {x=64,y=64} --地图偏移信息
mapImage        =   -1          --背景地图
mainTimer        =   -1   --主定时器
moveSpeed       =   2                    --用于调整整体速度
plane       =   {   
                    x=0,                            --我机位置:x坐标
                    y=0,                            --我机位置:y坐标
                    status=2,                   --我机姿态  1 2 3：左 中 右
                    canControl=false,    --我机是否能控制
                    superMode=false,    --我机是否无敌
                    dead    = true,           --我机是否已死亡
                    remain  =   3,            --我机剩余数量
                    superModeTimer = -1,    --无敌时间定时器
                    flashTimer  = -1               --无敌时,闪烁定时器
                }
planeImages     =   {}          --飞机图片资源

ENEMY_NUMBER      =   26	    --敌机总数
enemies                     =   {}       --敌机信息,数组,
            --每个元素为一个table：{x,y,speed,direction,style,dead}
enemyLostCount       =   0         --敌机死亡计数器
ballImage                  =   -1        --敌机子弹图片资源
enemyImage             =   -1        --敌机图片资源

BULLET_NUMBER   =   20	        --子弹总数
leftBullets     =   {}          --左侧子弹信息,数组,{x,y}
rightBullets    =   {}          --右侧子弹信息,数组,{x,y}
bullet          =   {           --子弹发射信息
                        timer=-1,   --发射定时器
                        number=1    --当前子弹编号
                    }   
buletImages     =   {}          --子弹图片资源(两种)

--我机火焰信息
deadFlame       =   {x=0,y=0,frame=0,timer=0}   
enemyFlames     =   {}      --敌机火焰信息,数组,
                            --{x=0,y=0,frame=0,timer}
deadImage       =   -1      --我机撞毁火焰图片资源
enemyDeadImage  =   -1      --敌机撞毁火焰图片资源

function Initialize()
    mainTimer     = InitTimer(12)
    --初始化敌机和子弹，都是处于死亡无效状态
    for i=1,ENEMY_NUMBER do
        enemies[i]  = {x=0,y=0,speed=0,dead=true,direction=0,style=0}  
    end
    DisableKeyDelay()       --禁止键盘延迟
    --初始化各子弹的坐标
    for i = 1,BULLET_NUMBER do
        leftBullets[i] =  {x = -100, y = -100}
        rightBullets[i] = {x = -100, y = -100}
    end
    --初始化子弹发射定时器：每隔 0.1 秒发射一次子弹
    bullet.timer     = InitTimer(100)   
    
    --初始化敌机火焰信息
    for i = 1,ENEMY_NUMBER do
        enemyFlames[i] = {  x=0,
                            y=0,
                            frame=0,
                            timer=InitTimer(150)}
    end
    --初始化我机死亡动画定时器
    deadFlame.timer = InitTimer(200)
    
    return 0
end

function LoadImages()
    mapImage        =   LoadImage("res\\map2.bmp")
    planeImages[1]  =   LoadImage("res\\plane_left.BMP")
    SetColorKey(planeImages[1],RGB(0,0,0))
    planeImages[2]  =   LoadImage("res\\plane_center.BMP")
    SetColorKey(planeImages[2],RGB(0,0,0))
    planeImages[3]  =   LoadImage("res\\plane_right.BMP")
    SetColorKey(planeImages[3],RGB(0,0,0))
    ballImage       =   LoadImage("res\\ball.bmp")
    SetColorKey(ballImage,RGB(0,0,0))
    enemyImage        =   LoadImage("res\\enemy.bmp")
    SetColorKey(enemyImage,RGB(0,0,0))
    buletImages[1]  =   LoadImage("res\\bullet_left.BMP")
    SetColorKey(buletImages[1],RGB(0,0,0))
    buletImages[2]  =   LoadImage("res\\bullet_right.BMP")
    SetColorKey(buletImages[2],RGB(0,0,0))
          
    enemyDeadImage   =   LoadImage("res\\flame.bmp")
    SetColorKey(enemyDeadImage,RGB(0,0,0))
    deadImage        =   LoadImage("res\\dead.bmp")
    SetColorKey(deadImage,RGB(0,0,0))

     return 0
end

function HandleFrame()
     --处理输入
    if 0 ~= ProcessInput() then 
        return 1        --返回非 0 值，游戏退出
    end
    CheckHit() --碰撞检测  
    EndTest()  --结束检测
    DrawMap()    
    DrawEnemy()
    DrawPlane()
    DrawBullet()
    DrawFlame()--绘制火焰
    DrawString()
    
    Show()
    return 0
end

function Terminate()
    return 0
end

function DrawBullet()
    for i = 1,BULLET_NUMBER do
        PaintImage(buletImages[1], 
                leftBullets[i].x, leftBullets[i].y)
        PaintImage(buletImages[2], 
                rightBullets[i].x, rightBullets[i].y)
    
        if GetTimerState(mainTimer) then
            leftBullets[i].x = leftBullets[i].x - 1
            --没发出的子弹y==0，并不断往上走，不会显示出来
            leftBullets[i].y = leftBullets[i].y - 12    
            
            rightBullets[i].x = rightBullets[i].x + 1
            rightBullets[i].y = rightBullets[i].y - 12
        end
    end    
end
function DrawPlane()
    ---[[
    if gameStatus ~= GAME_START then
        return 
    end
    --]]
    if plane.dead then
        plane.remain = plane.remain - 1   --剩余飞机数减一
        plane.dead  = false                                 --下一架飞机激活
        plane.superMode = true                        --无敌模式
        plane.canControl = false                       --开始时不能控制
        plane.x = WINDOW_WIDTH/2 - 25    --我机从底部中间位置开始进入
        plane.y = WINDOW_HEIGHT
        plane.superModeTimer = InitTimer(3000)    --无敌时间3秒
        plane.flashTimer = InitTimer(30)                    --延时30毫秒，
        --即每隔30毫秒才画一次我机，产生闪烁，无延时比较平滑不会产生闪烁
    end
    
  
    if not plane.canControl then
        if plane.y > WINDOW_HEIGHT - 100 then         
            --飞机刚出现时是无法控制的
            if GetTimerState(mainTimer) then
                plane.y = plane.y - moveSpeed --自动上升
                plane.status = 2
            end
        else
            plane.canControl = true
        end
    end
    
    if plane.superMode then
        if GetTimerState(plane.superModeTimer) then 
            --无敌时间已过！
            ClearTimer(plane.superModeTimer)
            ClearTimer(plane.flashTimer)
            plane.superMode = false
        end
        --无敌时的闪烁效果
        --延时30毫秒,产生闪烁，
        --即每隔30毫秒才画一次我机,无延时比较平滑不会产生闪烁
        if not GetTimerState(plane.flashTimer) then       
            return 
        end
    end
    
    PaintImage(planeImages[plane.status],plane.x,plane.y)
end

function DrawEnemy()
    for _ , e in ipairs(enemies) do
        if not e.dead  then             --如果敌机未毁，或子弹有效
            if e.style == 1 then        --敌机
                PaintImage(enemyImage,e.x,e.y)
            elseif e.style == 2 then    --子弹
                PaintImage(ballImage,e.x,e.y)
            end
            if GetTimerState(mainTimer) then
               --垂直下降速度e.speed=2~5 ,movespeed=2~5 用于调整整体速度
                e.y = e.y + e.speed + (moveSpeed-2)     
                --水平移动方向e.direction =-1 ~ 1 (左 中 右)
                e.x = e.x + e.direction 
            end
        end
        --敌机跑出屏底或死亡，则重生
        if e.y > WINDOW_HEIGHT or e.dead  then      
            e.x = GetRandomNumber(35,WINDOW_WIDTH - 35)
            e.y = GetRandomNumber(-35,0)
            e.speed = GetRandomNumber(2,5)          --/2-5；下降速度
            e.direction = GetRandomNumber(-1,1)    -- -1,0,1  左右移动方向
            e.style = GetRandomNumber(1,2)            -- 敌机1，子弹2
            
            e.dead  = false                                 --敌人复活
        end
    end
end

function DrawMap()
    if GetTimerState(mainTimer) then
        mapOffset.y = mapOffset.y - 1               --下卷动

        if mapOffset.y <= 0 then  
            mapOffset.y = 64
        end
        --根据飞机的状态，给地图添加左右卷动的效果
        mapOffset.x = mapOffset.x + plane.status - 2 
        if mapOffset.x <=0 then 
            mapOffset.x = 64
        end
        
        if mapOffset.x >64 then
            mapOffset.x = 1
        end
   end

    
    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            StretchPaintImage(mapImage,64*x-mapOffset.x, 64*y-mapOffset.y,64,64,0,0,0,0)
        end
    end
end


function DrawString()
    local x = (WINDOW_WIDTH - 140)/2
    local red = RGB(255,0,0)
    local blue = RGB(0,0,255)
    
    if gameStatus == GAME_LOG then      --欢迎画面
        TextOut("超级战机",             x,170,red)
        TextOut("子  弹: Ctr",          x,240,blue)
        TextOut("炸  弹: Space",        x,260,blue)
        TextOut("加  速:   +",          x,280,blue)
        TextOut("减  速:   -",          x,300,blue)
        TextOut("地  图: Return",       x,320,blue)
        TextOut("结  束: Esc",          x,340,blue)
        TextOut("全屏/窗口: ALT+ENTER", x,360,blue)
    
        PaintImage(planeImages[2],x-90,150)
        PaintImage(planeImages[2],x+180,150)
    end
    
    if gameStatus == GAME_START then        --游戏进行中
        --绘制剩余飞机
        for i=1,plane.remain do
            StretchPaintImage(planeImages[2],
                    10+(i-1)*25,WINDOW_HEIGHT - 30,20,20,
                    0,0,0,0)
        end
        TextOut("剩余飞机:" .. plane.remain,
                    10,WINDOW_HEIGHT - 50,blue)
        --绘制敌机（被击落的敌机计数）
        StretchPaintImage(enemyImage,
                WINDOW_WIDTH - 60, WINDOW_HEIGHT - 30,20,20,
                0,0,0,0)
        TextOut(enemyLostCount .. "",
                WINDOW_WIDTH-35, WINDOW_HEIGHT-25,red)
        TextOut("得分" .. enemyLostCount * 50,
                WINDOW_WIDTH/2-40, 5, blue)
    end
    
    if gameStatus == GAME_OVER then
        TextOut("Game Over",                                  
                x, WINDOW_HEIGHT/2-80, red)
        TextOut("共击落敌机 " .. enemyLostCount .. " 架",
                x, WINDOW_HEIGHT/2-30, blue)
        TextOut("按回车键继续",                               
                x, WINDOW_HEIGHT/2, blue)
        TextOut("超级战机: Lua 游戏!!!",                      
                x, WINDOW_HEIGHT/2+50, blue)
    end    
end

function ProcessInput()    
    --检测发射子弹
    if gameStatus == GAME_START and 
        plane.canControl == true then
        --左Control键按下，每隔0.1 秒发射一次
        if GetKeyState(DIK_LCONTROL) and 
            GetTimerState(bullet.timer) then  
            leftBullets[bullet.number].x = plane.x + 13
            leftBullets[bullet.number].y = plane.y
            rightBullets[bullet.number].x = plane.x + 32
            rightBullets[bullet.number].y = plane.y
            
            bullet.number = bullet.number + 1
            if bullet.number == BULLET_NUMBER then
                bullet.number  = 1
            end
        end
    end    
    
    --检测方向键，移动我机
    if plane.canControl and GetTimerState(mainTimer) then
		if GetKeyState(DIK_UP)      then	
            plane.y=plane.y-moveSpeed
            plane.status = 2  
        end
		if GetKeyState(DIK_DOWN)    then	
            plane.y=plane.y+moveSpeed 
            plane.status = 2 
        end
		if GetKeyState(DIK_LEFT)	then    
            plane.x=plane.x-moveSpeed  
            plane.status = 1  --左移飞机图案
        end
		if GetKeyState(DIK_RIGHT)	then    
            plane.x=plane.x+moveSpeed  
            plane.status = 3  --右移飞机图案
        end 

		--范围检查，禁止超出边界
		if plane.x<0                then	
            plane.x=0 
        end
		if plane.x>WINDOW_WIDTH-50	then    
            plane.x=WINDOW_WIDTH-50 
        end
		if plane.y<0	            then    
            plane.y=0 
        end
		if plane.y>WINDOW_HEIGHT-60	then    
            plane.y=WINDOW_HEIGHT-60 
        end
    end
    --方向键松开，恢复飞机的状态
    if GetKeyAction(DIK_UP,false) or
       GetKeyAction(DIK_DOWN,false) or
       GetKeyAction(DIK_LEFT,false) or
       GetKeyAction(DIK_RIGHT,false) then
            plane.status = 2 
    end

    --游戏速度控制
    if GetKeyAction(DIK_ADD,false)then        --加速
        moveSpeed = moveSpeed + 1
		if moveSpeed>5 then moveSpeed=5  end
    end
    
    if GetKeyAction(DIK_SUBTRACT,false) then   --减速
        moveSpeed = moveSpeed - 1
		if moveSpeed<2 then moveSpeed=2  end
    end
    
    if GetKeyState(DIK_LMENU) and 
       GetKeyAction(DIK_RETURN,false) then
       -- 左ALT + Enter 切换屏幕模式
        ToggleScreenMode()           
    elseif gameStatus ~= GAME_START then 
        if GetKeyAction(DIK_RETURN,false) then --开始游戏
            --开始游戏，进行初始化      
			for k = 1, ENEMY_NUMBER do
			    --所有敌机和子弹都是处于死亡无效状态
				enemies[k].dead=true  
			end
			enemyLostCount=0
			plane.dead = true
			plane.remain=3
			gameStatus=GAME_START
			moveSpeed=2
		end
    end
    
    if GetKeyState(DIK_ESCAPE) then     --退出
        return 1
    end
    
    return 0
end

function CheckHit()
    --游戏不在进行中
    if gameStatus ~= GAME_START then        
        return
    end
    --1、检测敌机是否被击落
    for i, e in ipairs(enemies) do
        --敌人未死
        if not e.dead then        
            if e.style == 2 then       --子弹
                --子弹无需碰撞检测
            elseif e.style == 1 and 
                  not OutOfRange(e.x, e.y) then    
                  --敌机，并且在窗口内
                for b = 1,BULLET_NUMBER do          
                    --与所有子弹做碰撞检测
                    --检测左子弹是否击中了该敌机
                    BulletHitEnemy(leftBullets[b],i)
                    --检测右子弹是否击中了该敌机
                    BulletHitEnemy(rightBullets[b],i)
                end
            end
        end
    end
    --2 检测我机是否撞毁
    --如为无敌状态不检测
    if not plane.superMode then   
        for _, e in ipairs(enemies) do
            --子弹或敌机未死亡无效，并且在窗口内        
            if e.dead ~= 0 and 
                not OutOfRange(e.x,e.y) then    
                if e.style == 2   then     --子弹
                    --检测我机与敌方子弹的碰撞
                    BallHitPlane(e)
                elseif e.style == 1 then   --敌机
                    --检测我机与敌机的碰撞
                    EnemyHitPlane(e)
                end
            end
        end
    end
end

-- 物体是否超出屏幕范围?
function OutOfRange(x,y)    
    if x<35 or x>WINDOW_WIDTH - 35 or 
       y<35 or y>WINDOW_HEIGHT - 35 then
		return true
	else
		return false
	end
end

--处理我机子弹与敌机的碰撞
--b: 子弹
--i: 敌机之索引
function BulletHitEnemy(b, i)
    local e = enemies[i]    --敌机
    if not OutOfRange(b.x,b.y) then
         if IntersectRect(e.x+7,e.y+3,22,26,
                          b.x,b.y,5,13) then
            e.dead = true     --敌机死亡
            --击落的敌机数增加1
            enemyLostCount  = enemyLostCount + 1       
            b.y=0             --使子弹消失            
            --设置火焰坐标，火焰比飞机大,
            --为使火焰中心与飞机中心对齐
            --x坐标左移10个点，y坐标上移8个点
            enemyFlames[i].x     =e.x-10
            enemyFlames[i].y     =e.y-8   
            --火焰状态设置为1，启动火焰动画            
            enemyFlames[i].frame = 1      
        end
   end
end

--处理敌机子弹与我机的碰撞
function BallHitPlane(e)
     if IntersectRect(e.x,e.y,8,8,
                plane.x+14,plane.y+16,23,41) then         
        e.dead  = true       --子弹无效
        plane.dead = true --我机死亡
        --设置火焰坐标，火焰比子弹大,
        --为使火焰中心与子弹中心对齐
        --x坐标左移29个点，y坐标上移29个点
        deadFlame.x = e.x - 29 
        deadFlame.y = e.y - 29
        --火焰状态设置为1，启动火焰动画            
        deadFlame.frame = 1
    end
end

--处理敌机与我机的碰撞
function EnemyHitPlane(e)
    if IntersectRect(e.x+7,e.y+3,22,26,
                plane.x+14,plane.y+16,23,41) then       
        e.dead  = true    --敌机死亡
        plane.dead = true --我机死亡
        --设置火焰正确位置，以敌机为中心，火焰比敌机大
        --为使火焰中心与子弹中心对齐
        --x坐标左移15个点，y坐标上移15个点 
        deadFlame.x = e.x - 15 
        deadFlame.y = e.y - 15
        --火焰状态设置为1，启动火焰动画         
        deadFlame.frame = 1      
     end
end

--结束检测
function EndTest()
    if plane.remain == -1  then --游戏结束
		gameStatus=GAME_OVER
	end
end

--绘制死亡动画
function DrawFlame() 
    --敌机死亡画面
    for _,ef in ipairs(enemyFlames) do
        if ef.frame ~= 0 then   --火焰已启动
            StretchPaintImage(enemyDeadImage, 
                       ef.x,ef.y,54,50,
                       (ef.frame - 1)*54,0,54,50)
            -- 150 毫秒更新新帧
            if GetTimerState(ef.timer) then     
                ef.frame = ef.frame + 1
                if ef.frame == 11 then
                    ef.frame = 0 --火焰停止播放
                end
            end
        end
    end
    --我机死亡画面
    if deadFlame.frame ~= 0 then    --火焰已启动
        StretchPaintImage(deadImage,
               deadFlame.x,deadFlame.y,66,66,
               (deadFlame.frame - 1) * 66,0,66,66)
        if GetTimerState(deadFlame.timer) then
            deadFlame.frame = deadFlame.frame + 1
            if deadFlame.frame == 9 then
                deadFlame.frame = 0 --火焰停止播放
            end
        end
    end
end

