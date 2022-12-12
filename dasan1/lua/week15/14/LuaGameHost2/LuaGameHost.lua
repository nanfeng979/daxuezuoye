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
forward         =   ""


function Initialize()
    mainTimer = InitTimer(12) -- 12ms一帧
    bgMusic = LoadMIDI("res/a.mid") -- 背景音乐
    DisableKeyDelay() -- 禁止键盘延迟，键盘输入必要
    return 0
end

function LoadImages()
    bgImage = LoadImage("res/MAP2.BMP") -- 加载背景图片资源

    playerImage = LoadImage("res/plane_center.BMP") -- 加载玩家图片资源
    SetColorKey(playerImage, RGB(0, 0, 0)) -- 将玩家的黑色像素设置为透明

    
    return 0
end

function HandleFrame()
    -- 全局锁帧
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- 绿色背景
    
    keyDown() -- 判断按键
    drawBg() -- 绘制背景
    
    PaintImage(playerImage, 100, 100) -- 绘制敌人

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

