WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua ��Ϸ"
enimyImage      =   -1  --�л�ID
mapImage        =   -1  --����ID
mapOffset       =   {x=64,y=64} --��ͼƫ����Ϣ
mainTimer       =   -1  --����ʱ��

function Initialize()
    mainTimer = InitTimer(12)   --12����
    return 0
end

function LoadImages()
    enimyImage = LoadImage("res\\ENEMY.bmp") --���صл�ͼƬ
    SetColorKey(enemyImage,RGB(0,0,0))  --���˵л�����(��)ɫ

    mapImage = LoadImage("res\\MAP2.bmp")      --���ر���ͼƬ

    return 0
end

function HandleFrame()
    DrawMap() --������Ϸ����
    DrawString()

    Show()--��ʾ����
    return 0
end

function Terminate()
    return 0
end


function DrawMap()
    if GetTimerState(mainTimer) then
        mapOffset.y = mapOffset.y - 1       --���¹���
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
    TextOut("ѧ��+����",300,300,RGB(255,255,255)) --���ʵ�λ����ʾ��ĸ�����Ϣ
end
