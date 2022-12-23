WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136��������Ϸ"
enemyImage      =   -1 -- ����
playerImage     =   -1 -- ���
playerShow      =   false -- �ж�����Ƿ���ʾ
deadImage       =   -1 -- ��������
bgImage         =   -1 -- ����
bgOffset        =   {x = 64, y = 64} -- ����ƫ��
mainTimer       =   -1 -- ����ʱ��
forward         =   "up"
moveSpeed       =   2 -- �һ����ƶ��ٶ�
plane   =   {
                x = 0, -- �һ���x����
                y = 0, -- �һ���y����
                status = 2, -- �һ�״̬ [1,2,3]��ʾ[��,��,��]
                canControl = false, -- �һ��Ƿ��ܿ���
                dead = true, -- �һ��Ƿ��޵�
                remain = 3, -- �һ�ʣ������
                superModeTimer = -1, -- �޵�ʱ��Ķ�ʱ��
                flashTimer = -1 -- �޵�ʱ�� ��˸��ʱ��
            }
planeImages = {} -- �ɻ�������Դ

ENEMY_NUMBER = 26 -- �л�����
enemies = {} -- �л���Ϣ[����]
ballImage = -1 -- �л��ӵ�ͼƬ
enemyImage = -1 -- �л�ͼƬ��Դ


function Initialize()
    mainTimer = InitTimer(12) -- 12msһ֡
    bgMusic = LoadMIDI("res/a.mid") -- ��������
    DisableKeyDelay() -- ��ֹ�����ӳ٣����������Ҫ
    
    -- ��ʼ���л����ӵ���һ��ʼʱ������״̬
    for i = 1, ENEMY_NUMBER do
        enemies[i] = {x=0, y=0, speed=0, dead=true,
                    direction=0, style=0}
    end
    return 0
end

function LoadImages()
    bgImage = LoadImage("res/MAP2.BMP") -- ���ر���ͼƬ��Դ

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
    -- ȫ����֡
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- ��ɫ����
    
    keyDown() -- �жϰ���
    drawBg() -- ���Ʊ���
    
    DrawEnemy() -- ���Ƶл�
    DrawPlane() -- ���Ʒɻ�
    
    -- ���ű�������
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
    -- �жϰ���
    if forward == "left" then
        bgOffset.x = bgOffset.x - 1
        
    elseif forward == "right" then
        bgOffset.x = bgOffset.x + 1
        
    elseif forward == "up" then
        bgOffset.y = bgOffset.y - 1
        
    elseif forward == "down" then
        bgOffset.y = bgOffset.y + 1
    end

    -- ƫ��������
    if bgOffset.x <= 0 or bgOffset.x >= 128 then
        bgOffset.x = 64
    end
    if bgOffset.y <= 0 or bgOffset.y >= 128 then
        bgOffset.y = 64
    end
    
    -- ���Ʊ���
    for x = 0, WINDOW_WIDTH / 64 + 2 do
        for y = 0, WINDOW_HEIGHT / 64 + 2 do
            StretchPaintImage(bgImage, 64 * x - bgOffset.x, 64 * y - bgOffset.y,
                              64, 64, 0, 0)
        end
    end
    
    TextOut("2220631136 + ������", 200, 100, RGB(255, 0, 0))
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
    for k, e in ipairs(enemies) do -- ��������ս��
        if not e.dead then
            if e.style == 1 then
                PaintImage(enemyImage, e.x, e.y) -- ���Ƶл�
            elseif e.style == 2 then
                PaintImage(ballImage, e.x, e.y) -- �����ӵ�
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

