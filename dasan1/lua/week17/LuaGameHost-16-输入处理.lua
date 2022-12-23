WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua 游戏"
enimyImage      =   -1  --敌机ID
mapImage        =   -1  --背景ID
mapOffset       =   {x=64,y=64} --地图偏移信息
mainTimer       =   -1  --主定时器
moveSpeed       =   2   --游戏速度（用于我机、敌机等速度控制）

--我机
planeImages     =   {}  --飞机图片资源
plane           =   {
                        x=0,                --我机位置:x坐标
                        y=0,                --我机位置:y坐标
                        status=2,           --我机姿态  1 2 3：左 中 右
                        canControl=false,   --我机是否能控制
                        superMode=false,    --我机是否无敌
                        dead    = true,     --我机是否已死亡
                        remain  =   3,      --我机剩余数量
                        superModeTimer = -1,--无敌时间定时器
                        flashTimer  = -1    --无敌时,闪烁定时器
                    }

--敌机
enemyImage      =   -1  --敌机图片资源
ballImage       =   -1  --敌机子弹图片资源
ENEMY_NUMBER    =   26	--敌机总数
enemies         =   {}  --敌机信息,数组，每个元素也为一个table：{x,y,speed,direction,style,dead}
enemyLostCount  =   0   --敌机死亡计数器

--游戏状态
GAME_LOG	    =   0   --欢迎画面
GAME_START	    =   1   --游戏已开始
GAME_OVER	    =   2   --游戏已结束
gameStatus      = 	GAME_LOG 	--游戏状态

--我机发射的子弹
BULLET_NUMBER   =   20	        --我机的子弹总对数
leftBullets     =   {}          --左侧子弹信息数组,每个子弹{x,y}
rightBullets    =   {}          --右侧子弹信息
bullet          =   {           --子弹发射信息
                        timer=-1,   --发射定时器
                        number=1    --当前子弹编号，最大为BULLET_NUMBER
                    }   
buletImages     =   {}          --子弹图片资源(两种)


function Initialize()
    mainTimer = InitTimer(12)   --主定时器，12毫秒，背景刷新、我机位置控制、敌机刷新等使用

    --初始化敌机和子弹，都是处于死亡无效状态
    for i=1,ENEMY_NUMBER do
        enemies[i]  = {x=0,y=0,speed=0,dead=true,direction=0,style=0}
    end
    
    --初始化我机子弹
    for i = 1,BULLET_NUMBER do
        leftBullets[i]  =   {x = -100, y = -100}    --只要y<=0即可
        rightBullets[i] =   {x = -100, y = -100}
    end   
    bullet.timer = InitTimer(100)   --每隔 0.1 秒发射一次子弹  
 
    DisableKeyDelay()   --禁止按键延迟
    return 0
end


function LoadImages()
    mapImage = LoadImage("res\\MAP2.bmp")      --加载背景图片
    planeImages[1]  =   LoadImage("res\\plane_left.BMP")
    SetColorKey(planeImages[1],RGB(0,0,0))
    planeImages[2]  =   LoadImage("res\\plane_center.BMP")
    SetColorKey(planeImages[2],RGB(0,0,0))
    planeImages[3]  =   LoadImage("res\\plane_right.BMP")
    SetColorKey(planeImages[3],RGB(0,0,0))

    enemyImage      =   LoadImage("res\\enemy.bmp")
    SetColorKey(enemyImage,RGB(0,0,0))
    ballImage       =   LoadImage("res\\ball.bmp")
    SetColorKey(ballImage,RGB(0,0,0))

    buletImages[1]  =   LoadImage("res\\bullet_left.BMP")
    SetColorKey(buletImages[1],RGB(0,0,0))
    buletImages[2]  =   LoadImage("res\\bullet_right.BMP")
    SetColorKey(buletImages[2],RGB(0,0,0))

    return 0
end


function HandleFrame()
    --输入处理
    if 0 ~= ProcessInput() then
        return 1    --返回非0值，游戏退出
    end

    DrawMap()
    DrawEnemy()
    DrawPlane()
    DrawBullet()
    DrawBullet()
    DrawString()

    Show()--显示画布
    return 0
end


function Terminate()
    return 0
end


function DrawMap()
    if GetTimerState(mainTimer) then
        mapOffset.y = mapOffset.y - 1       --向下滚动
        if mapOffset.y <= 0 then
            mapOffset.y = 64
        end
        
        --根据我机的姿态，给地图添加左右卷动的效果
        mapOffset.x = mapOffset.x + plane.status - 2
        if mapOffset.x <=0 then
            mapOffset.x = 64
        end
        if mapOffset.x >64 then
            mapOffset.x = 1
        end
    end --mainTimer

    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            StretchPaintImage(mapImage,
                64*x-mapOffset.x, 64*y-mapOffset.y,64,64,
                0,0,0,0)
        end
    end
end


function DrawString()
    local x     = (WINDOW_WIDTH - 140)/2
    local red   = RGB(255,0,0)
    local green = RGB(0,255,0)
    local white = RGB(255,255,255)
    TextOut("学号+姓名",700,50,white) 	--在适当位置显示你的个人信息

	if gameStatus == GAME_LOG then      --场景0，欢迎画面
		TextOut("超级战机",             x,170,red)
        TextOut("子  弹: Ctr",          x,240,green)
        TextOut("炸  弹: Space",        x,260,green)
        TextOut("加  速:   +",          x,280,green)
        TextOut("减  速:   -",          x,300,green)
        TextOut("地  图: Return",       x,320,green)
        TextOut("结  束: Esc",          x,340,green)
        PaintImage(planeImages[1],x-90,150)
        PaintImage(planeImages[3],x+180,150)
    end

    if gameStatus == GAME_START then        --场景1，游戏进行中
        TextOut("得分" .. enemyLostCount * 50,WINDOW_WIDTH/2-40, 5, green)

        --绘制敌机（被击落的敌机计数）
        StretchPaintImage(enemyImage,
                WINDOW_WIDTH - 80, WINDOW_HEIGHT - 35,35*2/3,35*2/3,
                0,0,0,0)
        TextOut(enemyLostCount .. "",
                WINDOW_WIDTH-35, WINDOW_HEIGHT-25,red)

        --绘制剩余飞机
        TextOut("剩余飞机:" .. plane.remain,10,WINDOW_HEIGHT - 60,green)
        for i=1,plane.remain do
            StretchPaintImage(planeImages[2],
                    15+(i-1)*40,WINDOW_HEIGHT - 35,50/2,60/2,
                    0,0,0,0)
        end
    end

    if gameStatus == GAME_OVER then         --场景2，游戏结束
        TextOut("Game Over",
                x, WINDOW_HEIGHT/2-80, red)
        TextOut("共击落敌机 " .. enemyLostCount .. " 架",
                x, WINDOW_HEIGHT/2-30, green)
        TextOut("按回车键继续",
                x, WINDOW_HEIGHT/2, green)
        TextOut("超级战机: Lua 游戏!!!",
                x, WINDOW_HEIGHT/2+50, green)
    end
end

function DrawPlane()
    --仅GAME_START状态下绘制Plane
    if gameStatus ~= GAME_START then
        return
    end
    
    if plane.dead then              --依据死亡状态配置我机的其它7组属性
        plane.remain = plane.remain - 1         --剩余飞机数减一
        plane.dead  = false                     --下一架飞机激活
        plane.superMode = true                  --无敌模式
        plane.canControl = false                --开始时不能控制飞机
        plane.x = WINDOW_WIDTH/2 - 25           --我机从屏幕底部中间位置开始向上进入
        plane.y = WINDOW_HEIGHT
        plane.superModeTimer = InitTimer(3000)  --无敌时间3秒
        plane.flashTimer = InitTimer(30)        --每30毫秒绘制我机一次，产生闪烁，无延时比较平滑不会产生闪烁
    end

    if not plane.canControl then    --飞机不可控状态下，修改相关属性以达到飞机自动向上飞行至一定高度的效果（初始状态飞机不可控）
        if plane.y > WINDOW_HEIGHT - 100 then   --自动向上飞行最高至 y = WINDOW_HEIGHT - 100 的高度
            if GetTimerState(mainTimer) then
                plane.y = plane.y - moveSpeed   --y轴坐标逐渐减小，偏移量即为飞行速度
                plane.status = 2                --飞机自动向上飞行时，选用2号姿态
            end
        else                                    --达到限定高度后，飞机状态改为可控
            plane.canControl = true
        end
    end

    if plane.superMode then         --根据飞机的无敌状态，决定是否呈现闪烁效果或修改无敌状态等相关属性
        if GetTimerState(plane.superModeTimer) then  --无敌时间已过！
            ClearTimer(plane.superModeTimer)
            ClearTimer(plane.flashTimer)
            plane.superMode = false
        end
        --无敌时的闪烁效果：每隔30毫秒绘制一次我机,无延时比较平滑不会产生闪烁
        if  not  GetTimerState(plane.flashTimer) then       --没有达到闪烁时间间隔，则不执行PaintImage
            return
        end
    end

    PaintImage(planeImages[plane.status],plane.x,plane.y)   --将我机的某一姿态显示在屏幕的(x,y)位置
end


function DrawEnemy()
    for _ , e in pairs(enemies) do  --遍历所有敌人

        if e.y > WINDOW_HEIGHT or e.dead  then  --敌人飞出屏幕或死亡，则重生（创建敌人对象）
            e.x = GetRandomNumber(35,WINDOW_WIDTH - 35)
            e.y = GetRandomNumber(-35,0)
            e.speed = GetRandomNumber(2,5)         --/2-5；下降速度
            e.direction = GetRandomNumber(-1,1)    -- -1,0,1  左右移动方向
            e.style = GetRandomNumber(1,2)         -- 敌机1，子弹2

            e.dead  = false                        --敌人复活
        end

		if not e.dead  then             --敌人没有死亡，则绘制对象、然后修改其位置
            if e.style == 1 then        --敌机
                PaintImage(enemyImage,e.x,e.y)
            elseif e.style == 2 then    --子弹
                PaintImage(ballImage,e.x,e.y)
            end
            if GetTimerState(mainTimer) then    --主定时器时间已到
               --垂直下降速度e.speed=2~5 ,movespeed=2~5 用于调整整体速度
                e.y = e.y + e.speed+ (moveSpeed-2)
                --水平移动方向e.direction =-1 ~ 1 (左 中 右)
                e.x = e.x + e.direction
            end --if
        end -- if not

    end --for
end --function


--检测到ESC键按下则返回1，其它情况返回0
function ProcessInput()
    --(1)非GAME_START状态下，按下主键盘的ENTER键开始游戏，进行初始化
    if gameStatus ~= GAME_START and GetKeyAction(DIK_RETURN,false) then
        for k = 1, ENEMY_NUMBER do
            enemies[k].dead=true
        end
        enemyLostCount=0
        plane.dead = true
        plane.remain=3
        gameStatus=GAME_START
        moveSpeed=2
    end

    --(2)任意状态下，ESC键退出游戏
    if GetKeyState(DIK_ESCAPE) then
        return 1    --检测到ESC键，返回1
    end

    --(3)按下方向键，改变我机位置及姿态
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
            plane.status = 1
        end
		if GetKeyState(DIK_RIGHT)	then
            plane.x=plane.x+moveSpeed
            plane.status = 3
        end

		--出界处理
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
    end --方向键检测

    --(4)方向键松开，恢复飞机的姿态
    if GetKeyAction(DIK_UP,false) or
       GetKeyAction(DIK_DOWN,false) or
       GetKeyAction(DIK_LEFT,false) or
       GetKeyAction(DIK_RIGHT,false) then
            plane.status = 2
    end

    --(5)游戏速度控制，+、-键
    if GetKeyAction(DIK_ADD,false)then        --加速
        moveSpeed = moveSpeed + 1
		if moveSpeed>5 then moveSpeed=5  end
    end

    if GetKeyAction(DIK_SUBTRACT,false) then   --减速
        moveSpeed = moveSpeed - 1
		if moveSpeed<2 then moveSpeed=2  end
    end
    
    --(6)检测左CONTROL键，发射子弹，即绘制可见的我机子弹
    if gameStatus == GAME_START     and
        plane.canControl            and
        GetKeyState(DIK_LCONTROL)   and  --左Control键按下， 
        GetTimerState(bullet.timer) then --每隔0.1 秒发射一次
            leftBullets[bullet.number].x = plane.x + 13
            leftBullets[bullet.number].y = plane.y
            rightBullets[bullet.number].x = plane.x + 32
            rightBullets[bullet.number].y = plane.y
            bullet.number = bullet.number + 1
            if bullet.number == BULLET_NUMBER then
                bullet.number  = 1
            end       
    end
    
    return 0    --没有检测到ESC键，返回0
end --function


function DrawBullet()
    for i = 1,BULLET_NUMBER do
        PaintImage(buletImages[1],
            leftBullets[i].x, leftBullets[i].y)
        PaintImage(buletImages[2],
            rightBullets[i].x, rightBullets[i].y)
        if GetTimerState(mainTimer) then
            leftBullets[i].x = leftBullets[i].x - 1
            leftBullets[i].y = leftBullets[i].y - 12
            rightBullets[i].x = rightBullets[i].x + 1
            rightBullets[i].y = rightBullets[i].y - 12
        end
        --[[没有发射子弹时，因其y<0，
        并随之画面刷新不断上移，所以不会显示出来]]
    end
end