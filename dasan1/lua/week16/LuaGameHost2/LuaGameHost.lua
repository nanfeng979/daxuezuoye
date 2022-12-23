WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136余庆祥游戏"
enemyImage      =   -1 -- 敌人
playerImage     =   -1 -- 玩家
playerShow      =   false -- 判断玩家是否显示
deadImage       =   -1 -- 死亡动画
bgImage         =   -1 -- 背景
bgOffset        =   {x = 64, y = 64} -- 背景偏移
mainTimer       =   -1 -- 主定时器
forward         =   "up"
moveSpeed       =   2 -- 我机的移动速度
plane   =   {
                x = 0, -- 我机的x坐标
                y = 0, -- 我机的y坐标
                status = 2, -- 我机状态 [1,2,3]表示[左,中,右]
                canControl = false, -- 我机是否能控制
                dead = true, -- 我机是否无敌
                remain = 3, -- 我机剩余数量
                superModeTimer = -1, -- 无敌时间的定时器
                flashTimer = -1 -- 无敌时， 闪烁定时器
            }
planeImages = {} -- 飞机动画资源

ENEMY_NUMBER = 26 -- 敌机总数
enemies = {} -- 敌机信息[数组]
ballImage = -1 -- 敌机子弹图片
enemyImage = -1 -- 敌机图片资源


function Initialize()
    mainTimer = InitTimer(12) -- 12ms一帧
    bgMusic = LoadMIDI("res/a.mid") -- 背景音乐
    DisableKeyDelay() -- 禁止键盘延迟，键盘输入必要
    
    -- 初始化敌机和子弹，一开始时是死亡状态
    for i = 1, ENEMY_NUMBER do
        enemies[i] = {x=0, y=0, speed=0, dead=true,
                    direction=0, style=0}
    end
    return 0
end

function LoadImages()
    bgImage = LoadImage("res/MAP2.BMP") -- 加载背景图片资源

    planeImages[1] = LoadImage("res/plane_left.BMP")
    SetColorKey(planeImages[1], RGB(0, 0, 0))
    planeImages[2] = LoadImage("res/plane_center.BMP")
    SetColorKey(planeImages[2], RGB(0, 0, 0))
    planeImages[3] = LoadImage("res/plane_right.BMP")
    SetColorKey(planeImages[3], RGB(0, 0, 0))

    ballImage = LoadImage("res/ball.bmp")
    SetColorKey(ballImage, RGB(0, 0, 0))
    enemyImage = LoadImage("res/enemy.bmp")
    SetColorKey(enemyImage, RGB(0, 0, 0))
    
    return 0
end

function HandleFrame()
    -- 全局锁帧
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- 绿色背景
    
    keyDown() -- 判断按键
    drawBg() -- 绘制背景
    
    DrawEnemy() -- 绘制敌机
    DrawPlane() -- 绘制飞机
    
    -- 播放背景音乐
    if not GetMIDIStatus(bgMusic) then
        PlayMIDI(bgMusic)
    end

    Show()
    
    end
    return 0
end

function Terminate()
    return 0
end

function keyDown()
    if GetKeyState(DIK_A) then
        forward = "left"
    end
    
    if GetKeyState(DIK_D) then
        forward = "right"
    end
    
    if GetKeyState(DIK_W) then
        forward = "up"
    end
    
    if GetKeyState(DIK_S) then
        forward = "down"
    end
end

function drawBg()
    -- 判断按键
    if forward == "left" then
        bgOffset.x = bgOffset.x - 1
        
    elseif forward == "right" then
        bgOffset.x = bgOffset.x + 1
        
    elseif forward == "up" then
        bgOffset.y = bgOffset.y - 1
        
    elseif forward == "down" then
        bgOffset.y = bgOffset.y + 1
    end

    -- 偏移量计算
    if bgOffset.x <= 0 or bgOffset.x >= 128 then
        bgOffset.x = 64
    end
    if bgOffset.y <= 0 or bgOffset.y >= 128 then
        bgOffset.y = 64
    end
    
    -- 绘制背景
    for x = 0, WINDOW_WIDTH / 64 + 2 do
        for y = 0, WINDOW_HEIGHT / 64 + 2 do
            StretchPaintImage(bgImage, 64 * x - bgOffset.x, 64 * y - bgOffset.y,
                              64, 64, 0, 0)
        end
    end
    
    TextOut("2220631136 + 余庆祥", 200, 100, RGB(255, 0, 0))
end


function DrawPlane()
    if plane.dead then
        plane.remain = plane.remain - 1
        plane.dead = false
        plane.superMode = true
        plane.canControl = false
        plane.x = WINDOW_WIDTH / 2 - 25
        plane.y = WINDOW_HEIGHT
        plane.superModeTimer = InitTimer(3000)
        plane.flashTimer = InitTimer(300)
    end
  
    if not plane.canControl then
        if plane.y > WINDOW_HEIGHT - 100 then
            if GetTimerState(mainTimer) then
                plane.y = plane.y - moveSpeed
                plane.status = 2
            end
        else
            plane.canControl = true
        end
    end
    
    if plane.superMode then
        if GetTimerState(plane.superModeTimer) then
            ClearTimer(plane.superModeTimer)
            ClearTimer(plane.flashTimer)
            plane.superMode = false
        end
        
        if not GetTimerState(plane.flashTimer) then
            return
        end
    end
    
    PaintImage(planeImages[plane.status], plane.x, plane.y)
end

function DrawEnemy()
    for k, e in ipairs(enemies) do -- 遍历所有战机
        if not e.dead then
            if e.style == 1 then
                PaintImage(enemyImage, e.x, e.y) -- 绘制敌机
            elseif e.style == 2 then
                PaintImage(ballImage, e.x, e.y) -- 绘制子弹
            end
            
            if GetTimerState(mainTimer) then
                e.y = e.y + e.speed * moveSpeed
                e.x = e.x + e.speed * e.direction 
            end
        end
        
        if e.y > WINDOW_HEIGHT or e.dead then
            e.x = GetRandomNumber(35, WINDOW_WIDTH - 35)
            e.y = GetRandomNumber(-35, 0)
            e.speed = GetRandomNumber(2, 5)
            e.direction = GetRandomNumber(-1, 1)
            e.style = GetRandomNumber(1, 2)
            e.dead = false
        end
    end
    
    

end

