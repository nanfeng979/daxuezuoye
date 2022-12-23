WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua ��Ϸ"
enimyImage      =   -1  --�л�ID
mapImage        =   -1  --����ID
mapOffset       =   {x=64,y=64} --��ͼƫ����Ϣ
mainTimer       =   -1  --����ʱ��
rollingDirection=   -1  --��ͼ��������

function Initialize()
    mainTimer = InitTimer(12)
    return 0
end

function LoadImages()
    enimyImage = LoadImage("res\\ENEMY.bmp") --����ͼƬ
    SetColorKey(enemyImage,RGB(0,0,0))  --���˱���(��)ɫ
    mapImage = LoadImage("res\\MAP2.bmp")
    
    DisableKeyDelay() --��ֹ�����ӳ�
    return 0
end

function HandleFrame()
    DrawMap() --������Ϸ����
    PaintImage(enemyImage,100,100) --���Ƶл�
    TextOut("ѧ��+����",200,500,RGB(255,255,255))   
    Show()--��ʾ����  
    return 0
end

function Terminate()
    return 0
end

function DrawMap()
    -- WSAD--1234
    if GetKeyState(DIK_W) then rollingDirection = 1 end --����
    if GetKeyState(DIK_S) then rollingDirection = 2 end --����
    if GetKeyState(DIK_A) then rollingDirection = 3 end --����
    if GetKeyState(DIK_D) then rollingDirection = 4 end --����

    --ÿ12�������һ�ε�ͼƫ��
    if GetTimerState(mainTimer) then
        if rollingDirection == 2 or rollingDirection == 1 then  --��ֱ����
            mapOffset.y = mapOffset.y - 1   --����ƫ������1             
            if mapOffset.y <= 0 then
                mapOffset.y = 64
            end
        end
        if rollingDirection == 3 or rollingDirection == 4 then  --ˮƽ����
		    mapOffset.x = mapOffset.x -1    --����ƫ������1
            if mapOffset.x <= 0 then
                mapOffset.x = 64
            end
        end
    end
    
    --�����زĸ��ݵ�ͼ�������򣬴�ָ��ƫ��λ�ÿ�ʼ��������
    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            if rollingDirection == 1 then  --����
                StretchPaintImage(mapImage,
                64*x, 64*y+mapOffset.y-64 ,64,64,
                0,0,0,0)
            end
           	if rollingDirection == 2 then  --����
                StretchPaintImage(mapImage,
                64*x, 64*y-mapOffset.y ,64,64,
                0,0,0,0)
            end
		    if rollingDirection == 3 then  --����
                StretchPaintImage(mapImage,
                64*x+mapOffset.x-64, 64*y ,64,64,
				0,0,0,0)
            end
            if rollingDirection == 4 then  --����
                StretchPaintImage(mapImage,
                64*x-mapOffset.x, 64*y ,64,64,
                0,0,0,0)
           end
        end
    end
    
end
