WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136��������Ϸ"
enemyImage      =   -1 -- ����
playerShow      =   false -- �ж�����Ƿ���ʾ

function Initialize()
    bgMusic = LoadMIDI("res/a.mid") -- ��������
    DisableKeyDelay() -- ��ֹ�����ӳ٣����������Ҫ
    return 0
end

function LoadImages()
    playerImage = LoadImage("res/plane_center.BMP") -- �������ͼƬ��Դ
    SetColorKey(playerImage, RGB(0, 0, 0)) -- ����ҵĺ�ɫ��������Ϊ͸��

    enemyImage = LoadImage("res/ENEMY.bmp") -- ���ص���ͼƬ��Դ
    SetColorKey(enemyImage, RGB(0, 0, 0)) -- �����˵ĺ�ɫ��������Ϊ͸��
    
    deadImage = LoadImage("res/dead.BMP") -- ��������������Դ
    SetColorKey(deadImage, RGB(0, 0, 0)) -- �����������ĺ�ɫ��������Ϊ͸��
   
    return 0
end

function HandleFrame()
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- ��ɫ����
    
    PaintImage(enemyImage, 100, 100) -- ���Ƶ���
    if playerShow then
        PaintImage(playerImage, 100, 400) -- �������
    end
    
    PaintImage(deadImage, 250, 100) -- ������������
    deadN = 4 -- �������Ƶ�N֡
    StretchPaintImage(deadImage, 250 + (deadN - 1) * 66, 300, 66, 66, 66 * (deadN - 1), 0, 66, 66) -- ��������������ĳһ֡
    
    TextOut("2220631136+������", 200, 500, RGB(0, 0, 255))
    
    -- ���ű�������
    if not GetMIDIStatus(bgMusic) then
        PlayMIDI(bgMusic)
    end
    
    -- ����alt��enter��
    if GetKeyState(DIK_LMENU) then 
        if GetKeyAction(DIK_RETURN, true) then
            ToggleScreenMode() -- ȫ��
        end
    end
    
    -- ���������
    if GetMouseButtonState(0) then
        playerShow = true
    end
    
    Show()
    
    return 0
end

function Terminate()
    return 0
end


