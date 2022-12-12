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
forward         =   ""


function Initialize()
    mainTimer = InitTimer(12) -- 12msһ֡
    bgMusic = LoadMIDI("res/a.mid") -- ��������
    DisableKeyDelay() -- ��ֹ�����ӳ٣����������Ҫ
    return 0
end

function LoadImages()
    bgImage = LoadImage("res/MAP2.BMP") -- ���ر���ͼƬ��Դ

    playerImage = LoadImage("res/plane_center.BMP") -- �������ͼƬ��Դ
    SetColorKey(playerImage, RGB(0, 0, 0)) -- ����ҵĺ�ɫ��������Ϊ͸��

    
    return 0
end

function HandleFrame()
    -- ȫ����֡
    if GetTimerState(mainTimer) then
    
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- ��ɫ����
    
    keyDown() -- �жϰ���
    drawBg() -- ���Ʊ���
    
    PaintImage(playerImage, 100, 100) -- ���Ƶ���

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

