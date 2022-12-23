WINDOW_WIDTH    =   800 * 2
WINDOW_HEIGHT   =   600 * 1
WINDOW_WIDTH_LOCAL    =   800
WINDOW_HEIGHT_LOCAL   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136锟斤拷锟斤拷锟斤拷锟斤拷戏"
gameData        = {mapLen = 2, speed = 4, isOver = false, isQuit = false}


distance = 0
offset          = {x = 1}

bgData         = {}
for i = 1, gameData.mapLen do
    bgData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 0, w = 800, h = 600}
end

-- todo 写成和Sprite一样
-- 玩家 -- [framse:总帧数, frame:当前第几帧, jsjump:正在跳, isDown:正在掉, jumpTime:悬空的时间, jumpTimer:悬空的定时器, canKeyDown:可以接收键盘消息]
playerInitData = {x = 200, y = 400, w = 100, h = 102}
playerData      = {x = 200, y = 400, w = 100, h = 102, frames = 8, frame = 1, isjump = false, isDown = false, jumpTime = 1.5, jumpTimer = 1.5, canKeyDown = true} -- 包含Ani

-- 地面 -- [dcol: 修正碰撞范围]
groundData      = {}
for i = 1, gameData.mapLen do
    groundData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 460, w = 672 - 100, h = 149, visible = true, collisionable = true, dcol = {dw = 60, dh = 0}}
end

-- 星星
starData        = {anchor = {x = 64, y = 0}, random = true}
for i = 1, gameData.mapLen do
    starData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 400, w = 32, h = 32, collisionable = true, visible = true, name = "star"}
end
getStarsNum     = 0
getStarLock     = false

-- 椅子
tableData        = {scale = {x = 1, y = 1}, random = true}
for i = 1, gameData.mapLen do
    tableData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 440, w = 150, h = 84, collisionable = false, visible = true, name = "table"}
end




function Initialize()
    mainTimer = InitTimer(12) -- 12ms一帧
    playerFPS = InitTimer(60) -- 控制玩家动画帧率
    
    
    tableData[1].x = 400
    tableData[1].d = WINDOW_WIDTH_LOCAL - tableData[1].x
    tableData[2].x = 200 + WINDOW_WIDTH_LOCAL
    tableData[2].d = WINDOW_WIDTH_LOCAL * 2 - tableData[2].x
    
    starData[1].x = 100
    starData[1].d = WINDOW_WIDTH_LOCAL - starData[1].x
    starData[2].x = 200 + WINDOW_WIDTH_LOCAL
    starData[2].d = WINDOW_WIDTH_LOCAL * 2 - starData[2].x

    --bgMusic = LoadMIDI("res/a.mid") -- 背景音乐
    DisableKeyDelay() -- 禁止键盘延迟，键盘输入必要
    
    return 0
end

function LoadImages()
    -- 加载背景资源
    bgData.img = LoadImage("res/bg/env.bmp")
    -- 加载地面资源
    groundData.img = LoadImage("res/bg/ground.bmp")
    SetColorKey(groundData.img, RGB(0, 255, 0))
    
    -- 加载星星资源
    starData.img = LoadImage("res/other/star.bmp")
    SetColorKey(starData.img, RGB(0, 255, 0))
    
    -- 加载椅子资源
    tableData.img = LoadImage("res/other/tabl1.bmp")
    SetColorKey(tableData.img, RGB(0, 255, 0))
    


    -- 加载玩家资源
    for i = 1, 9 do
        playerData[i] = LoadImage("res/Character/run/b" .. tostring(i - 1)  .. ".bmp")
        SetColorKey(playerData[i], RGB(0, 255, 0))
    end
    playerData.dumpUpImg = LoadImage("res/Character/jump/jumpUp.bmp")
    SetColorKey(playerData.dumpUpImg, RGB(0, 255, 0))
    playerData.dumpDownImg = LoadImage("res/Character/jump/jumpDown.bmp")
    SetColorKey(playerData.dumpDownImg, RGB(0, 255, 0))


    
    return 0
end

function HandleFrame()
    if gameData.isQuit then
        return 1
    end

    -- 全局锁帧
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH_LOCAL, WINDOW_HEIGHT_LOCAL) -- 绿色背景
    
    
    globlLogin() -- 游戏全局逻辑
    
    InputMessage() -- 输入消息函数
    
    -- 渲染背景
    DrawBg()
    
    
    DrawSprite(groundData) -- 渲染地面
    DrawSprite(starData) -- 渲染星星
    DrawSprite(tableData) -- 渲染椅子

    DrawPlayer() -- 渲染人物
    
    physic(playerData) -- 赋予物理系统
    
    
    -- 碰撞
    collider(starData, playerData, addStarNum) -- 星星与玩家
    collider(tableData, playerData, pushBackPlayer) -- 椅子与玩家
    collider(groundData, playerData, stakePlayer) -- 地面与玩家


    --if not GetMIDIStatus(bgMusic) then
    --    PlayMIDI(bgMusic)
    --end
    DrawUI()
    Show()
    
    end
    return 0
end

function Terminate()
    return 0
end


-- 渲染背景函数
function DrawBg()
    for i = 1, gameData.mapLen do
        if bgData[i].x + WINDOW_WIDTH_LOCAL <= 0 then
            bgData[i].x = WINDOW_WIDTH_LOCAL
        end
        PaintImage(bgImage, bgData[i].x, bgData[i].y)
        bgData[i].x = bgData[i].x - gameData.speed
    end
end

-- 自定义函数 start
-- 增加已经获得的星星的个数
function addStarNum(obj1, obj2)
    if obj1.visible then
        obj1.visible = false
        getStarsNum = getStarsNum + 1 -- 星星个数+1
    end
end

-- 向后推玩家
function pushBackPlayer(obj1, obj2)
    obj2.x = obj2.x - gameData.speed
end

-- 地面支撑玩家
function stakePlayer(obj1, obj2)
    if obj2.y > playerInitData.y and not playerData.isDown then
        obj2.y = playerInitData.y
    end
    
    TextOut("isCollider", 400, 200, RGB(255, 0, 0))
end

-- 自定义函数 end

-- 碰撞函数
function collider(obj1s, obj2, action) -- todo: 获得星星函数要独立出来
    for i = 1, gameData.mapLen do
        if not obj1s[i].dcol then
            obj1s[i].dcol = {dw = 0, dh = 0}
        end
    
        -- 与物体碰撞，当前只实现与玩家碰撞 -- todo: 转到别处
        if obj1s[i].collisionable and
            obj1s[i].x <= obj2.x + obj2.w and
            obj1s[i].x + obj1s[i].w - obj1s[i].dcol.dw >= obj2.x and
            obj1s[i].y + obj1s[i].h >= obj2.y and
            obj1s[i].y <= obj2.y + obj2.h
                then
            action(obj1s[i], obj2)
        end
        
    end
end


-- 渲染精灵
function DrawSprite(sprObj)
    
    for i = 1, gameData.mapLen do
        -- 对象不断左移
        sprObj[i].x = sprObj[i].x - offset.x * gameData.speed

        
        -- 初始化 -- todo: 转到别处
        if not sprObj[i].d then
            sprObj[i].d = WINDOW_WIDTH_LOCAL
        end
        
        if not sprObj.anchor then
            sprObj.anchor = {x = 0, y = 0}
        end
        if not sprObj.scale then
            sprObj.scale = {x = 1, y = 1}
        end
        
        -- 对象左移直到离开左边宽口时 -- todo: 判断条件补充对象的宽度
        if sprObj[i].x + sprObj[i].d <= 0 then
            -- 重置对象到窗口最右边的外面
            sprObj[i].x = WINDOW_WIDTH_LOCAL
            if sprObj[i].name == "table" then
                sprObj[i].y = GetRandomNumber(390, 440)
                -- todo: 补充星星，移到别处
            end

            -- 如果要随机的位置
            if sprObj.random then
                -- 生成一个随机的位置
                distance = GetRandomNumber(100, WINDOW_WIDTH_LOCAL - sprObj[i].w)
                sprObj[i].x = sprObj[i].x + distance
            end
            
            -- 重新计算对象与屏幕右边的距离
            sprObj[i].d = 2 * WINDOW_WIDTH_LOCAL - sprObj[i].x
            -- 重新设置为可见
            sprObj[i].visible = true
        end
        

        -- 可见时才渲染
        if sprObj[i].visible then
            StretchPaintImage(sprObj.img, sprObj[i].x * sprObj.scale.x, sprObj[i].y * sprObj.scale.y, sprObj[i].w, sprObj[i].h, 
            sprObj.anchor.x, sprObj.anchor.y, sprObj[i].w, sprObj[i].h)
        end
        
        
    end
end

-- 渲染动画精灵
function DrawAni(aniObj, FPS)
    PaintImage(aniObj[aniObj.frame], aniObj.x, aniObj.y)
    
    if GetTimerState(FPS) then -- 跳到下一帧
        aniObj.frame = aniObj.frame + 1
        if aniObj.frame > aniObj.frames + 1 then
            aniObj.frame = 1
        end
    end
end

function DrawPlayer()
    -- 跳跃时控制最高距离
    if playerData.isJump and playerData.y <= 280 then
        playerData.y = 280
    end
    -- 跳跃后降落时控制最低距离
    if playerData.isJump and playerData.y >= 400 then
        if not playerData.isDown then
            playerData.y = 400
        end
       
    end
    
    -- 检测是否掉下地面
    if playerData.y > 400 then
        playerData.isDown = true
    else
        playerData.isDown = false
    end
    
    -- 定时器计算
    if playerData.jumpTimer > 0 then -- 计算悬空时间
        playerData.jumpTimer = playerData.jumpTimer - 1 / (1000 / 12)
    else
        playerData.isJump = false
    end
    
    if playerData.isJump then
        playerData.y = playerData.y - 5
        TextOut(playerData.jumpTimer, 300, 300, RGB(255, 0, 0))
        PaintImage(playerData.dumpUpImg, playerData.x, playerData.y)
    elseif not playerData.isJump and playerData.y < 400 then
        PaintImage(playerData.dumpDownImg, playerData.x, playerData.y)
    else
        playerData.canKeyDown = true -- 恢复接收键盘消息
        playerData.jumpTimer = playerData.jumpTime -- 重置定时器
        DrawAni(playerData, playerFPS)  -- 渲染动画
    end
 
end

-- 绘制UI函数
function DrawUI()
    
    -- 游戏结束时
    if gameData.isOver then
        TextOut("游戏结束", 300, 200, RGB(255, 0, 0))
        TextOut("当前获得的星星个数为: " .. tostring(getStarsNum), 300, 250, RGB(255, 0, 0))
        TextOut("重新游戏请按Enter键", 300, 300, RGB(255, 0, 0))
        TextOut("推出游戏请按ESC键", 300, 350, RGB(255, 0, 0))
        return
    end
    
    TextOut("当前获得的星星个数为：" .. tostring(getStarsNum), 100, 100, RGB(255, 0, 0))
    TextOut(playerData.y, 200, 200, RGB(255, 0, 0))
    if playerData.isJump then
        TextOut("yes", 300, 200, RGB(255, 0, 0))
    else 
        TextOut("no", 300, 200, RGB(255, 0, 0))
    end
    
end

-- 消息输入响应函数
function InputMessage()
    --if GetKeyAction(DIK_SPACE, true) then
    if GetKeyState(DIK_SPACE) then
        if playerData.canKeyDown then
            playerData.isJump = true
            playerData.canKeyDown = false
        end
    else
        playerData.isJump = false
    end
    
    -- 关闭游戏
    if GetKeyState(DIK_ESCAPE) then
        gameData.isQuit = true
    end
end

-- 游戏全局逻辑函数
function globlLogin()
    -- 玩家x轴离开屏幕外
    if playerData.x + playerData.w <= 0 then
        gameData.isOver = true
    end
    
    -- 玩家y轴离开屏幕外
    if playerData.y > WINDOW_HEIGHT_LOCAL then
        gameData.isOver = true
    end
    
    
    if gameData.isOver then
        gameData.speed = 0
    end
end

-- 物理特性
function physic(obj)
    obj.y = obj.y + 3
end



