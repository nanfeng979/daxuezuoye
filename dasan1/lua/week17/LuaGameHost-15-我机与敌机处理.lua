WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua ��Ϸ"
enimyImage      =   -1  --�л�ID
mapImage        =   -1  --����ID
mapOffset       =   {x=64,y=64} --��ͼƫ����Ϣ
mainTimer       =   -1  --����ʱ��
moveSpeed       =   2   --��Ϸ�ٶȣ������һ����л����ٶȿ��ƣ�

--�һ�
planeImages     =   {}  --�ɻ�ͼƬ��Դ
plane           =   {
                        x=0,                --�һ�λ��:x����
                        y=0,                --�һ�λ��:y����
                        status=2,           --�һ���̬  1 2 3���� �� ��
                        canControl=false,   --�һ��Ƿ��ܿ���
                        superMode=false,    --�һ��Ƿ��޵�
                        dead    = true,     --�һ��Ƿ�������
                        remain  =   3,      --�һ�ʣ������
                        superModeTimer = -1,--�޵�ʱ�䶨ʱ��
                        flashTimer  = -1    --�޵�ʱ,��˸��ʱ��
                    }

--�л�
enemyImage      =   -1  --�л�ͼƬ��Դ
ballImage       =   -1  --�л��ӵ�ͼƬ��Դ
ENEMY_NUMBER    =   26	--�л�����
enemies         =   {}  --�л���Ϣ,���飬ÿ��Ԫ��ҲΪһ��table��{x,y,speed,direction,style,dead}


function Initialize()
    mainTimer = InitTimer(12)   --����ʱ����12���룬����ˢ�¡��һ�λ�ÿ��ơ��л�ˢ�µ�ʹ��

    --��ʼ���л����ӵ������Ǵ���������Ч״̬
    for i=1,ENEMY_NUMBER do
        enemies[i]  = {x=0,y=0,speed=0,dead=true,direction=0,style=0}
    end

    return 0
end


function LoadImages()
    mapImage = LoadImage("res\\MAP2.bmp")      --���ر���ͼƬ
    planeImages[1]  =   LoadImage("res\\plane_left.BMP")
    SetColorKey(planeImages[1],RGB(0,0,0))
    planeImages[2]  =   LoadImage("res\\plane_center.BMP")
    SetColorKey(planeImages[2],RGB(0,0,0))
    planeImages[3]  =   LoadImage("res\\plane_right.BMP")
    SetColorKey(planeImages[3],RGB(0,0,0))

    enemyImage      =   LoadImage("res\\enemy.bmp")
    SetColorKey(enemyImage,RGB(0,0,0))
    ballImage       =   LoadImage("res\\ball.bmp")
    SetColorKey(ballImage,RGB(0,0,0))

    DisableKeyDelay() --��ֹ�����ӳ�
    return 0
end


function HandleFrame()
    DrawMap()
    DrawEnemy()
    DrawPlane()
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
    PaintImage(planeImages[1],300-90,300)
    PaintImage(planeImages[3],300+180,300)
end


function DrawPlane()
    if plane.dead then              --��������״̬�����һ�������7������
        plane.remain = plane.remain - 1         --ʣ��ɻ�����һ
        plane.dead  = false                     --��һ�ܷɻ�����
        plane.superMode = true                  --�޵�ģʽ
        plane.canControl = false                --��ʼʱ���ܿ��Ʒɻ�
        plane.x = WINDOW_WIDTH/2 - 25           --�һ�����Ļ�ײ��м�λ�ÿ�ʼ���Ͻ���
        plane.y = WINDOW_HEIGHT
        plane.superModeTimer = InitTimer(3000)  --�޵�ʱ��3��
        plane.flashTimer = InitTimer(30)        --ÿ30��������һ�һ�Σ�������˸������ʱ�Ƚ�ƽ�����������˸
    end

    if not plane.canControl then    --�ɻ����ɿ�״̬�£��޸���������Դﵽ�ɻ��Զ����Ϸ�����һ���߶ȵ�Ч������ʼ״̬�ɻ����ɿأ�
        if plane.y > WINDOW_HEIGHT - 100 then   --�Զ����Ϸ�������� y = WINDOW_HEIGHT - 100 �ĸ߶�
            if GetTimerState(mainTimer) then
                plane.y = plane.y - moveSpeed   --y�������𽥼�С��ƫ������Ϊ�����ٶ�
                plane.status = 2                --�ɻ��Զ����Ϸ���ʱ��ѡ��2����̬
            end
        else                                    --�ﵽ�޶��߶Ⱥ󣬷ɻ�״̬��Ϊ�ɿ�
            plane.canControl = true
        end
    end

    if plane.superMode then         --���ݷɻ����޵�״̬�������Ƿ������˸Ч�����޸��޵�״̬���������
        if GetTimerState(plane.superModeTimer) then  --�޵�ʱ���ѹ���
            ClearTimer(plane.superModeTimer)
            ClearTimer(plane.flashTimer)
            plane.superMode = false
        end
        --�޵�ʱ����˸Ч����ÿ��30�������һ���һ�,����ʱ�Ƚ�ƽ�����������˸
        if  not  GetTimerState(plane.flashTimer) then       --û�дﵽ��˸ʱ��������ִ��PaintImage
            return
        end
    end

    PaintImage(planeImages[plane.status],plane.x,plane.y)   --���һ���ĳһ��̬��ʾ����Ļ��(x,y)λ��
end


function DrawEnemy()
    for _ , e in pairs(enemies) do  --�������е���

        if e.y > WINDOW_HEIGHT or e.dead  then  --���˷ɳ���Ļ�����������������������˶���
            e.x = GetRandomNumber(35,WINDOW_WIDTH - 35)
            e.y = GetRandomNumber(-35,0)
            e.speed = GetRandomNumber(2,5)         --/2-5���½��ٶ�
            e.direction = GetRandomNumber(-1,1)    -- -1,0,1  �����ƶ�����
            e.style = GetRandomNumber(1,2)         -- �л�1���ӵ�2

            e.dead  = false                        --���˸���
        end

		if not e.dead  then             --����û������������ƶ���Ȼ���޸���λ��
            if e.style == 1 then        --�л�
                PaintImage(enemyImage,e.x,e.y)
            elseif e.style == 2 then    --�ӵ�
                PaintImage(ballImage,e.x,e.y)
            end
            if GetTimerState(mainTimer) then    --����ʱ��ʱ���ѵ�
               --��ֱ�½��ٶ�e.speed=2~5 ,movespeed=2~5 ���ڵ��������ٶ�
                e.y = e.y + e.speed+ (moveSpeed-2)
                --ˮƽ�ƶ�����e.direction =-1 ~ 1 (�� �� ��)
                e.x = e.x + e.direction
            end --if
        end -- if not

    end --for
end --function
