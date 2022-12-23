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


function Initialize()
    mainTimer = InitTimer(12)   --主定时器，12毫秒，背景刷新、我机位置控制、敌机刷新等使用

    --初始化敌机和子弹，都是处于死亡无效状态
    for i=1,ENEMY_NUMBER do
        enemies[i]  = {x=0,y=0,speed=0,dead=true,direction=0,style=0}
    end

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

    DisableKeyDelay() --禁止按键延迟
    return 0
end


function HandleFrame()
    DrawMap()
    DrawEnemy()
    DrawPlane()
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
    end

    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            StretchPaintImage(mapImage,
                64*x, 64*y-mapOffset.y,64,64,
                0,0,0,0)
        end
    end
end


function DrawString()
    TextOut("学号+姓名",300,300,RGB(255,255,255)) --在适当位置显示你的个人信息
    PaintImage(planeImages[1],300-90,300)
    PaintImage(planeImages[3],300+180,300)
end


function DrawPlane()
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
