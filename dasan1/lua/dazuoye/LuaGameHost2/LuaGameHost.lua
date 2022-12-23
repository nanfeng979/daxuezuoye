WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136余庆祥游戏"
mapLen          = 2
globlSpeed      = 3
envImage        =   -1 -- 背景
envOffset       =   {x = 0, y = 0} -- 背景的偏移量
groundImage     =   -1 --   地面
groundData        = {w = 672, h = 149}
groundsAllData  = {}
for i = 1, mapLen do
    groundsAllData[i] = {x = 0, y = 0}
end

groundsDataOnce = true
playerImage     =   {} -- 玩家
playerData      =   {x = 50, y = 0, w = 100, h = 102} -- 玩家信息
playerImageIndex = 0 -- 玩家图片下标
starImage       = -1 -- 星星
starData          = {w = 32, h = 32}
starsAllData    = {}
for i = 1, mapLen do
    starsAllData[i] = {x = 0, y = 0}
end

starsDataOnce   = true
getStars        = 0 -- 已获得星星的数量
canGetStar      = {true, true, true, true, true, true, true, true, true}
otherOffset     = 1
obImage         = -1 -- 障碍物
obData            = {w = 176, h = 160}
obsAllData      = {}
for i = 1, mapLen do
    obsAllData[i] = {x = 0, y = 0}
end
obsDataOnce     = true


function Initialize()
    mainTimer = InitTimer(12) -- 12ms一帧
    playerTimer = InitTimer(60)
    
    
    
    --bgMusic = LoadMIDI("res/a.mid") -- 背景音乐
    DisableKeyDelay() -- 禁止键盘延迟，键盘输入必要
    
    return 0
end

function LoadImages()
    envImage = LoadImage("res/bg/env.bmp") -- 加载背景图片资源
    groundImage = LoadImage("res/bg/ground.bmp") -- 加载地面
    SetColorKey(groundImage, RGB(0, 255, 0))
    


    -- 加载人物资源
    for i = 0, 8 do
        playerImage[i] = LoadImage("res/Character/run/b" .. tostring(i)  .. ".bmp")
        SetColorKey(playerImage[i], RGB(0, 255, 0))
    end
    
    starImage = LoadImage("res/other/star.bmp") -- 加载星星
    SetColorKey(starImage, RGB(0, 255, 0))
    
    obImage = LoadImage("res/other/ob.bmp") -- 加载障碍物
    SetColorKey(obImage, RGB(0, 255, 0))


    
    return 0
end

function HandleFrame()
    -- 全局锁帧
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- 绿色背景
    

    OffsetCal() -- 计算偏移量
    key() -- 按键操作
    
    DrawBg() -- 渲染背景相关

    
    DrawPlayer() -- 渲染玩家
    DrawStarsOnce() -- 渲染星星
    

    
    DrawSprite() -- 渲染所有精灵
    
    
    
    
    DrawUI() -- 渲染分数


    -- 播放背景音乐
    --if not GetMIDIStatus(bgMusic) then
    --    PlayMIDI(bgMusic)
    --end

    Show()
    
    end
    return 0
end

function Terminate()
    return 0
end



function OffsetCal()
    envOffset.x = envOffset.x + 1 * globlSpeed
    if envOffset.x >= 800 then
        envOffset.x = 0
    end
    
    otherOffset = otherOffset + 1
end

function DrawBg()
    PaintImage(bgImage, 0 - envOffset.x, 0)
    PaintImage(bgImage, WINDOW_WIDTH - envOffset.x, 0)
    DrawGround() -- 渲染地面
    DrawObstacle() -- 渲染障碍物
    

end

function DrawGround()  
    if groundsDataOnce then
        for i = 1, mapLen do
            groundsAllData[i].x = WINDOW_WIDTH * (i - 1)
            groundsAllData[i].y = WINDOW_HEIGHT - 50
        end
        groundsDataOnce = false
    end
    
    for i = 1, mapLen do
        
    
        StretchPaintImage(groundImage, groundsAllData[i].x - globlSpeed * otherOffset, groundsAllData[i].y, groundData.w, groundData.h, 0, 0, groundData.w, groundData.h)
    end
    

end

function DrawPlayer()

    PaintImage(playerImage[playerImageIndex], playerData.x, playerData.y)
    
    if GetTimerState(playerTimer) then -- 控制动画速率
        playerImageIndex = playerImageIndex + 1
        if playerImageIndex > 8 then
            playerImageIndex = 0
        end
    end
end


function DrawStarsOnce()
    if starsDataOnce then
        for i = 1, mapLen do
            starsAllData[i].x = GetRandomNumber(100, 300) + WINDOW_WIDTH * (i - 1)
            starsAllData[i].y = WINDOW_HEIGHT - 50 - 40 - GetRandomNumber(0, 100)
        end
        starsDataOnce = false
    end
    
    for i = 1, mapLen do
        -- 玩家与星星的碰撞
        if starsAllData[i].x - globlSpeed * otherOffset <= playerData.x + playerData.w
            and starsAllData[i].y + starData.h - 14>= playerData.y
            and starsAllData[i].y <= playerData.y + playerData.h then
            if canGetStar[i] then
                getStars = getStars + 1
                canGetStar[i] = false
            end
        else
            if canGetStar[i] then
                StretchPaintImage(starImage, starsAllData[i].x - globlSpeed * otherOffset, starsAllData[i].y, starData.w, starData.h, 64, 0, starData.w, starData.h)
            end
            
        end
    end
end

function DrawObstacle()

    if obsDataOnce then
        for i = 1, mapLen do
            obsAllData[i].x = GetRandomNumber(400, 600) + WINDOW_WIDTH * (i - 1)
            --obsAllData[i].x = 400
            obsAllData[i].y = WINDOW_HEIGHT - 50 - 40 - GetRandomNumber(0, 50)
            --obsAllData[i].y = WINDOW_HEIGHT - 100
        end
        obsDataOnce = false
    end
    
    for i = 1, mapLen do
        -- 障碍物与玩家的碰撞
        if obsAllData[i].x - globlSpeed * otherOffset <= playerData.x + playerData.w - 30
            and obsAllData[i].x - globlSpeed * otherOffset > playerData.x
            --and obsAllData[i].y <= playerData.y
            and obsAllData[i].y <= playerData.y + playerData.h then
            
                
                --if playerData.y + playerData.h >= obsAllData[i].y then
                    --playerData.y = obsAllData[i].y - obData.h
                --else    
                    playerData.x = playerData.x - globlSpeed -- 玩家后退
                --end
        end    
        
        --StretchPaintImage(obImage, obsAllData[i].x - globlSpeed * otherOffset, obsAllData[i].y, obData.w * 0.7, obData.h * 0.7, 0, 0, obData.w, obData.h)

    end

end

function key()
    -- 玩家跳起来
    if GetKeyState(DIK_SPACE) then
        playerData.y = 350
    else
        playerData.y = 470
    end 
end

function DrawUI()
    TextOut("已获得的星星个数: " .. tostring(getStars), 100, 100, RGB(255, 0, 0))
    
    if playerData.x <= 0 - playerData.w / 2 then
        TextOut("游戏结束: ", 200, 100, RGB(255, 0, 0))
    end
    
    --if playerData.x > groundData.w then
     --   TextOut("降落", 300, 100, RGB(255, 0, 0))
    --end
end

function DrawSprite()
    
    for i = 1, mapLen do

        StretchPaintImage(obImage, obsAllData[i].x - globlSpeed * otherOffset, obsAllData[i].y, obData.w * 0.7, obData.h * 0.7, 0, 0, obData.w, obData.h)

    end
end





