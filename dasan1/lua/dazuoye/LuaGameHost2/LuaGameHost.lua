WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136��������Ϸ"
mapLen          = 2
globlSpeed      = 3
envImage        =   -1 -- ����
envOffset       =   {x = 0, y = 0} -- ������ƫ����
groundImage     =   -1 --   ����
groundData        = {w = 672, h = 149}
groundsAllData  = {}
for i = 1, mapLen do
    groundsAllData[i] = {x = 0, y = 0}
end

groundsDataOnce = true
playerImage     =   {} -- ���
playerData      =   {x = 50, y = 0, w = 100, h = 102} -- �����Ϣ
playerImageIndex = 0 -- ���ͼƬ�±�
starImage       = -1 -- ����
starData          = {w = 32, h = 32}
starsAllData    = {}
for i = 1, mapLen do
    starsAllData[i] = {x = 0, y = 0}
end

starsDataOnce   = true
getStars        = 0 -- �ѻ�����ǵ�����
canGetStar      = {true, true, true, true, true, true, true, true, true}
otherOffset     = 1
obImage         = -1 -- �ϰ���
obData            = {w = 176, h = 160}
obsAllData      = {}
for i = 1, mapLen do
    obsAllData[i] = {x = 0, y = 0}
end
obsDataOnce     = true


function Initialize()
    mainTimer = InitTimer(12) -- 12msһ֡
    playerTimer = InitTimer(60)
    
    
    
    --bgMusic = LoadMIDI("res/a.mid") -- ��������
    DisableKeyDelay() -- ��ֹ�����ӳ٣����������Ҫ
    
    return 0
end

function LoadImages()
    envImage = LoadImage("res/bg/env.bmp") -- ���ر���ͼƬ��Դ
    groundImage = LoadImage("res/bg/ground.bmp") -- ���ص���
    SetColorKey(groundImage, RGB(0, 255, 0))
    


    -- ����������Դ
    for i = 0, 8 do
        playerImage[i] = LoadImage("res/Character/run/b" .. tostring(i)  .. ".bmp")
        SetColorKey(playerImage[i], RGB(0, 255, 0))
    end
    
    starImage = LoadImage("res/other/star.bmp") -- ��������
    SetColorKey(starImage, RGB(0, 255, 0))
    
    obImage = LoadImage("res/other/ob.bmp") -- �����ϰ���
    SetColorKey(obImage, RGB(0, 255, 0))


    
    return 0
end

function HandleFrame()
    -- ȫ����֡
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- ��ɫ����
    

    OffsetCal() -- ����ƫ����
    key() -- ��������
    
    DrawBg() -- ��Ⱦ�������

    
    DrawPlayer() -- ��Ⱦ���
    DrawStarsOnce() -- ��Ⱦ����
    

    
    DrawSprite() -- ��Ⱦ���о���
    
    
    
    
    DrawUI() -- ��Ⱦ����


    -- ���ű�������
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
    DrawGround() -- ��Ⱦ����
    DrawObstacle() -- ��Ⱦ�ϰ���
    

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
    
    if GetTimerState(playerTimer) then -- ���ƶ�������
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
        -- ��������ǵ���ײ
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
        -- �ϰ�������ҵ���ײ
        if obsAllData[i].x - globlSpeed * otherOffset <= playerData.x + playerData.w - 30
            and obsAllData[i].x - globlSpeed * otherOffset > playerData.x
            --and obsAllData[i].y <= playerData.y
            and obsAllData[i].y <= playerData.y + playerData.h then
            
                
                --if playerData.y + playerData.h >= obsAllData[i].y then
                    --playerData.y = obsAllData[i].y - obData.h
                --else    
                    playerData.x = playerData.x - globlSpeed -- ��Һ���
                --end
        end    
        
        --StretchPaintImage(obImage, obsAllData[i].x - globlSpeed * otherOffset, obsAllData[i].y, obData.w * 0.7, obData.h * 0.7, 0, 0, obData.w, obData.h)

    end

end

function key()
    -- ���������
    if GetKeyState(DIK_SPACE) then
        playerData.y = 350
    else
        playerData.y = 470
    end 
end

function DrawUI()
    TextOut("�ѻ�õ����Ǹ���: " .. tostring(getStars), 100, 100, RGB(255, 0, 0))
    
    if playerData.x <= 0 - playerData.w / 2 then
        TextOut("��Ϸ����: ", 200, 100, RGB(255, 0, 0))
    end
    
    --if playerData.x > groundData.w then
     --   TextOut("����", 300, 100, RGB(255, 0, 0))
    --end
end

function DrawSprite()
    
    for i = 1, mapLen do

        StretchPaintImage(obImage, obsAllData[i].x - globlSpeed * otherOffset, obsAllData[i].y, obData.w * 0.7, obData.h * 0.7, 0, 0, obData.w, obData.h)

    end
end





