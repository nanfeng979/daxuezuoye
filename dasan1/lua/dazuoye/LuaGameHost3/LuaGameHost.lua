WINDOW_WIDTH    =   800 * 2
WINDOW_HEIGHT   =   600 * 1
WINDOW_WIDTH_LOCAL    =   800
WINDOW_HEIGHT_LOCAL   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136��������Ϸ"
gameData        = {mapLen = 2, speed = 4, isOver = false, isQuit = false}


distance = 0
offset          = {x = 1}

bgData         = {}
for i = 1, gameData.mapLen do
    bgData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 0, w = 800, h = 600}
end

-- todo д�ɺ�Spriteһ��
-- ��� -- [framse:��֡��, frame:��ǰ�ڼ�֡, jsjump:������, isDown:���ڵ�, jumpTime:���յ�ʱ��, jumpTimer:���յĶ�ʱ��, canKeyDown:���Խ��ռ�����Ϣ]
playerInitData = {x = 200, y = 400, w = 100, h = 102}
playerData      = {x = 200, y = 400, w = 100, h = 102, frames = 8, frame = 1, isjump = false, isDown = false, jumpTime = 1.5, jumpTimer = 1.5, canKeyDown = true} -- ����Ani

-- ���� -- [dcol: ������ײ��Χ]
groundData      = {}
for i = 1, gameData.mapLen do
    groundData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 460, w = 672 - 100, h = 149, visible = true, collisionable = true, dcol = {dw = 60, dh = 0}}
end

-- ����
starData        = {anchor = {x = 64, y = 0}, random = true}
for i = 1, gameData.mapLen do
    starData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 400, w = 32, h = 32, collisionable = true, visible = true, name = "star"}
end
getStarsNum     = 0
getStarLock     = false

-- ����
tableData        = {scale = {x = 1, y = 1}, random = true}
for i = 1, gameData.mapLen do
    tableData[i] = {x = (i - 1) * WINDOW_WIDTH_LOCAL, y = 440, w = 150, h = 84, collisionable = false, visible = true, name = "table"}
end




function Initialize()
    mainTimer = InitTimer(12) -- 12msһ֡
    playerFPS = InitTimer(60) -- ������Ҷ���֡��
    
    
    tableData[1].x = 400
    tableData[1].d = WINDOW_WIDTH_LOCAL - tableData[1].x
    tableData[2].x = 200 + WINDOW_WIDTH_LOCAL
    tableData[2].d = WINDOW_WIDTH_LOCAL * 2 - tableData[2].x
    
    starData[1].x = 100
    starData[1].d = WINDOW_WIDTH_LOCAL - starData[1].x
    starData[2].x = 200 + WINDOW_WIDTH_LOCAL
    starData[2].d = WINDOW_WIDTH_LOCAL * 2 - starData[2].x

    --bgMusic = LoadMIDI("res/a.mid") -- ��������
    DisableKeyDelay() -- ��ֹ�����ӳ٣����������Ҫ
    
    return 0
end

function LoadImages()
    -- ���ر�����Դ
    bgData.img = LoadImage("res/bg/env.bmp")
    -- ���ص�����Դ
    groundData.img = LoadImage("res/bg/ground.bmp")
    SetColorKey(groundData.img, RGB(0, 255, 0))
    
    -- ����������Դ
    starData.img = LoadImage("res/other/star.bmp")
    SetColorKey(starData.img, RGB(0, 255, 0))
    
    -- ����������Դ
    tableData.img = LoadImage("res/other/tabl1.bmp")
    SetColorKey(tableData.img, RGB(0, 255, 0))
    


    -- ���������Դ
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

    -- ȫ����֡
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH_LOCAL, WINDOW_HEIGHT_LOCAL) -- ��ɫ����
    
    
    globlLogin() -- ��Ϸȫ���߼�
    
    InputMessage() -- ������Ϣ����
    
    -- ��Ⱦ����
    DrawBg()
    
    
    DrawSprite(groundData) -- ��Ⱦ����
    DrawSprite(starData) -- ��Ⱦ����
    DrawSprite(tableData) -- ��Ⱦ����

    DrawPlayer() -- ��Ⱦ����
    
    physic(playerData) -- ��������ϵͳ
    
    
    -- ��ײ
    collider(starData, playerData, addStarNum) -- ���������
    collider(tableData, playerData, pushBackPlayer) -- ���������
    collider(groundData, playerData, stakePlayer) -- ���������


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


-- ��Ⱦ��������
function DrawBg()
    for i = 1, gameData.mapLen do
        if bgData[i].x + WINDOW_WIDTH_LOCAL <= 0 then
            bgData[i].x = WINDOW_WIDTH_LOCAL
        end
        PaintImage(bgImage, bgData[i].x, bgData[i].y)
        bgData[i].x = bgData[i].x - gameData.speed
    end
end

-- �Զ��庯�� start
-- �����Ѿ���õ����ǵĸ���
function addStarNum(obj1, obj2)
    if obj1.visible then
        obj1.visible = false
        getStarsNum = getStarsNum + 1 -- ���Ǹ���+1
    end
end

-- ��������
function pushBackPlayer(obj1, obj2)
    obj2.x = obj2.x - gameData.speed
end

-- ����֧�����
function stakePlayer(obj1, obj2)
    if obj2.y > playerInitData.y and not playerData.isDown then
        obj2.y = playerInitData.y
    end
    
    TextOut("isCollider", 400, 200, RGB(255, 0, 0))
end

-- �Զ��庯�� end

-- ��ײ����
function collider(obj1s, obj2, action) -- todo: ������Ǻ���Ҫ��������
    for i = 1, gameData.mapLen do
        if not obj1s[i].dcol then
            obj1s[i].dcol = {dw = 0, dh = 0}
        end
    
        -- ��������ײ����ǰֻʵ���������ײ -- todo: ת����
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


-- ��Ⱦ����
function DrawSprite(sprObj)
    
    for i = 1, gameData.mapLen do
        -- ���󲻶�����
        sprObj[i].x = sprObj[i].x - offset.x * gameData.speed

        
        -- ��ʼ�� -- todo: ת����
        if not sprObj[i].d then
            sprObj[i].d = WINDOW_WIDTH_LOCAL
        end
        
        if not sprObj.anchor then
            sprObj.anchor = {x = 0, y = 0}
        end
        if not sprObj.scale then
            sprObj.scale = {x = 1, y = 1}
        end
        
        -- ��������ֱ���뿪��߿��ʱ -- todo: �ж������������Ŀ��
        if sprObj[i].x + sprObj[i].d <= 0 then
            -- ���ö��󵽴������ұߵ�����
            sprObj[i].x = WINDOW_WIDTH_LOCAL
            if sprObj[i].name == "table" then
                sprObj[i].y = GetRandomNumber(390, 440)
                -- todo: �������ǣ��Ƶ���
            end

            -- ���Ҫ�����λ��
            if sprObj.random then
                -- ����һ�������λ��
                distance = GetRandomNumber(100, WINDOW_WIDTH_LOCAL - sprObj[i].w)
                sprObj[i].x = sprObj[i].x + distance
            end
            
            -- ���¼����������Ļ�ұߵľ���
            sprObj[i].d = 2 * WINDOW_WIDTH_LOCAL - sprObj[i].x
            -- ��������Ϊ�ɼ�
            sprObj[i].visible = true
        end
        

        -- �ɼ�ʱ����Ⱦ
        if sprObj[i].visible then
            StretchPaintImage(sprObj.img, sprObj[i].x * sprObj.scale.x, sprObj[i].y * sprObj.scale.y, sprObj[i].w, sprObj[i].h, 
            sprObj.anchor.x, sprObj.anchor.y, sprObj[i].w, sprObj[i].h)
        end
        
        
    end
end

-- ��Ⱦ��������
function DrawAni(aniObj, FPS)
    PaintImage(aniObj[aniObj.frame], aniObj.x, aniObj.y)
    
    if GetTimerState(FPS) then -- ������һ֡
        aniObj.frame = aniObj.frame + 1
        if aniObj.frame > aniObj.frames + 1 then
            aniObj.frame = 1
        end
    end
end

function DrawPlayer()
    -- ��Ծʱ������߾���
    if playerData.isJump and playerData.y <= 280 then
        playerData.y = 280
    end
    -- ��Ծ����ʱ������;���
    if playerData.isJump and playerData.y >= 400 then
        if not playerData.isDown then
            playerData.y = 400
        end
       
    end
    
    -- ����Ƿ���µ���
    if playerData.y > 400 then
        playerData.isDown = true
    else
        playerData.isDown = false
    end
    
    -- ��ʱ������
    if playerData.jumpTimer > 0 then -- ��������ʱ��
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
        playerData.canKeyDown = true -- �ָ����ռ�����Ϣ
        playerData.jumpTimer = playerData.jumpTime -- ���ö�ʱ��
        DrawAni(playerData, playerFPS)  -- ��Ⱦ����
    end
 
end

-- ����UI����
function DrawUI()
    
    -- ��Ϸ����ʱ
    if gameData.isOver then
        TextOut("��Ϸ����", 300, 200, RGB(255, 0, 0))
        TextOut("��ǰ��õ����Ǹ���Ϊ: " .. tostring(getStarsNum), 300, 250, RGB(255, 0, 0))
        TextOut("������Ϸ�밴Enter��", 300, 300, RGB(255, 0, 0))
        TextOut("�Ƴ���Ϸ�밴ESC��", 300, 350, RGB(255, 0, 0))
        return
    end
    
    TextOut("��ǰ��õ����Ǹ���Ϊ��" .. tostring(getStarsNum), 100, 100, RGB(255, 0, 0))
    TextOut(playerData.y, 200, 200, RGB(255, 0, 0))
    if playerData.isJump then
        TextOut("yes", 300, 200, RGB(255, 0, 0))
    else 
        TextOut("no", 300, 200, RGB(255, 0, 0))
    end
    
end

-- ��Ϣ������Ӧ����
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
    
    -- �ر���Ϸ
    if GetKeyState(DIK_ESCAPE) then
        gameData.isQuit = true
    end
end

-- ��Ϸȫ���߼�����
function globlLogin()
    -- ���x���뿪��Ļ��
    if playerData.x + playerData.w <= 0 then
        gameData.isOver = true
    end
    
    -- ���y���뿪��Ļ��
    if playerData.y > WINDOW_HEIGHT_LOCAL then
        gameData.isOver = true
    end
    
    
    if gameData.isOver then
        gameData.speed = 0
    end
end

-- ��������
function physic(obj)
    obj.y = obj.y + 3
end



