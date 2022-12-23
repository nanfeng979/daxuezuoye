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
enemyLostCount  =   0   --�л�����������

--��Ϸ״̬
GAME_LOG	    =   0   --��ӭ����
GAME_START	    =   1   --��Ϸ�ѿ�ʼ
GAME_OVER	    =   2   --��Ϸ�ѽ���
gameStatus      = 	GAME_LOG 	--��Ϸ״̬

--�һ�������ӵ�
BULLET_NUMBER   =   20	        --�һ����ӵ��ܶ���
leftBullets     =   {}          --����ӵ���Ϣ����,ÿ���ӵ�{x,y}
rightBullets    =   {}          --�Ҳ��ӵ���Ϣ
bullet          =   {           --�ӵ�������Ϣ
                        timer=-1,   --���䶨ʱ��
                        number=1    --��ǰ�ӵ���ţ����ΪBULLET_NUMBER
                    }   
buletImages     =   {}          --�ӵ�ͼƬ��Դ(����)


function Initialize()
    mainTimer = InitTimer(12)   --����ʱ����12���룬����ˢ�¡��һ�λ�ÿ��ơ��л�ˢ�µ�ʹ��

    --��ʼ���л����ӵ������Ǵ���������Ч״̬
    for i=1,ENEMY_NUMBER do
        enemies[i]  = {x=0,y=0,speed=0,dead=true,direction=0,style=0}
    end
    
    --��ʼ���һ��ӵ�
    for i = 1,BULLET_NUMBER do
        leftBullets[i]  =   {x = -100, y = -100}    --ֻҪy<=0����
        rightBullets[i] =   {x = -100, y = -100}
    end   
    bullet.timer = InitTimer(100)   --ÿ�� 0.1 �뷢��һ���ӵ�  
 
    DisableKeyDelay()   --��ֹ�����ӳ�
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

    buletImages[1]  =   LoadImage("res\\bullet_left.BMP")
    SetColorKey(buletImages[1],RGB(0,0,0))
    buletImages[2]  =   LoadImage("res\\bullet_right.BMP")
    SetColorKey(buletImages[2],RGB(0,0,0))

    return 0
end


function HandleFrame()
    --���봦��
    if 0 ~= ProcessInput() then
        return 1    --���ط�0ֵ����Ϸ�˳�
    end

    DrawMap()
    DrawEnemy()
    DrawPlane()
    DrawBullet()
    DrawBullet()
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
        
        --�����һ�����̬������ͼ������Ҿ���Ч��
        mapOffset.x = mapOffset.x + plane.status - 2
        if mapOffset.x <=0 then
            mapOffset.x = 64
        end
        if mapOffset.x >64 then
            mapOffset.x = 1
        end
    end --mainTimer

    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            StretchPaintImage(mapImage,
                64*x-mapOffset.x, 64*y-mapOffset.y,64,64,
                0,0,0,0)
        end
    end
end


function DrawString()
    local x     = (WINDOW_WIDTH - 140)/2
    local red   = RGB(255,0,0)
    local green = RGB(0,255,0)
    local white = RGB(255,255,255)
    TextOut("ѧ��+����",700,50,white) 	--���ʵ�λ����ʾ��ĸ�����Ϣ

	if gameStatus == GAME_LOG then      --����0����ӭ����
		TextOut("����ս��",             x,170,red)
        TextOut("��  ��: Ctr",          x,240,green)
        TextOut("ը  ��: Space",        x,260,green)
        TextOut("��  ��:   +",          x,280,green)
        TextOut("��  ��:   -",          x,300,green)
        TextOut("��  ͼ: Return",       x,320,green)
        TextOut("��  ��: Esc",          x,340,green)
        PaintImage(planeImages[1],x-90,150)
        PaintImage(planeImages[3],x+180,150)
    end

    if gameStatus == GAME_START then        --����1����Ϸ������
        TextOut("�÷�" .. enemyLostCount * 50,WINDOW_WIDTH/2-40, 5, green)

        --���Ƶл���������ĵл�������
        StretchPaintImage(enemyImage,
                WINDOW_WIDTH - 80, WINDOW_HEIGHT - 35,35*2/3,35*2/3,
                0,0,0,0)
        TextOut(enemyLostCount .. "",
                WINDOW_WIDTH-35, WINDOW_HEIGHT-25,red)

        --����ʣ��ɻ�
        TextOut("ʣ��ɻ�:" .. plane.remain,10,WINDOW_HEIGHT - 60,green)
        for i=1,plane.remain do
            StretchPaintImage(planeImages[2],
                    15+(i-1)*40,WINDOW_HEIGHT - 35,50/2,60/2,
                    0,0,0,0)
        end
    end

    if gameStatus == GAME_OVER then         --����2����Ϸ����
        TextOut("Game Over",
                x, WINDOW_HEIGHT/2-80, red)
        TextOut("������л� " .. enemyLostCount .. " ��",
                x, WINDOW_HEIGHT/2-30, green)
        TextOut("���س�������",
                x, WINDOW_HEIGHT/2, green)
        TextOut("����ս��: Lua ��Ϸ!!!",
                x, WINDOW_HEIGHT/2+50, green)
    end
end

function DrawPlane()
    --��GAME_START״̬�»���Plane
    if gameStatus ~= GAME_START then
        return
    end
    
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


--��⵽ESC�������򷵻�1�������������0
function ProcessInput()
    --(1)��GAME_START״̬�£����������̵�ENTER����ʼ��Ϸ�����г�ʼ��
    if gameStatus ~= GAME_START and GetKeyAction(DIK_RETURN,false) then
        for k = 1, ENEMY_NUMBER do
            enemies[k].dead=true
        end
        enemyLostCount=0
        plane.dead = true
        plane.remain=3
        gameStatus=GAME_START
        moveSpeed=2
    end

    --(2)����״̬�£�ESC���˳���Ϸ
    if GetKeyState(DIK_ESCAPE) then
        return 1    --��⵽ESC��������1
    end

    --(3)���·�������ı��һ�λ�ü���̬
    if plane.canControl and GetTimerState(mainTimer) then
		if GetKeyState(DIK_UP)      then
            plane.y=plane.y-moveSpeed
            plane.status = 2
        end
		if GetKeyState(DIK_DOWN)    then
            plane.y=plane.y+moveSpeed
            plane.status = 2
        end
		if GetKeyState(DIK_LEFT)	then
            plane.x=plane.x-moveSpeed
            plane.status = 1
        end
		if GetKeyState(DIK_RIGHT)	then
            plane.x=plane.x+moveSpeed
            plane.status = 3
        end

		--���紦��
		if plane.x<0                then
            plane.x=0
        end
		if plane.x>WINDOW_WIDTH-50	then
            plane.x=WINDOW_WIDTH-50
        end
		if plane.y<0	            then
            plane.y=0
        end
		if plane.y>WINDOW_HEIGHT-60	then
            plane.y=WINDOW_HEIGHT-60
        end
    end --��������

    --(4)������ɿ����ָ��ɻ�����̬
    if GetKeyAction(DIK_UP,false) or
       GetKeyAction(DIK_DOWN,false) or
       GetKeyAction(DIK_LEFT,false) or
       GetKeyAction(DIK_RIGHT,false) then
            plane.status = 2
    end

    --(5)��Ϸ�ٶȿ��ƣ�+��-��
    if GetKeyAction(DIK_ADD,false)then        --����
        moveSpeed = moveSpeed + 1
		if moveSpeed>5 then moveSpeed=5  end
    end

    if GetKeyAction(DIK_SUBTRACT,false) then   --����
        moveSpeed = moveSpeed - 1
		if moveSpeed<2 then moveSpeed=2  end
    end
    
    --(6)�����CONTROL���������ӵ��������ƿɼ����һ��ӵ�
    if gameStatus == GAME_START     and
        plane.canControl            and
        GetKeyState(DIK_LCONTROL)   and  --��Control�����£� 
        GetTimerState(bullet.timer) then --ÿ��0.1 �뷢��һ��
            leftBullets[bullet.number].x = plane.x + 13
            leftBullets[bullet.number].y = plane.y
            rightBullets[bullet.number].x = plane.x + 32
            rightBullets[bullet.number].y = plane.y
            bullet.number = bullet.number + 1
            if bullet.number == BULLET_NUMBER then
                bullet.number  = 1
            end       
    end
    
    return 0    --û�м�⵽ESC��������0
end --function


function DrawBullet()
    for i = 1,BULLET_NUMBER do
        PaintImage(buletImages[1],
            leftBullets[i].x, leftBullets[i].y)
        PaintImage(buletImages[2],
            rightBullets[i].x, rightBullets[i].y)
        if GetTimerState(mainTimer) then
            leftBullets[i].x = leftBullets[i].x - 1
            leftBullets[i].y = leftBullets[i].y - 12
            rightBullets[i].x = rightBullets[i].x + 1
            rightBullets[i].y = rightBullets[i].y - 12
        end
        --[[û�з����ӵ�ʱ������y<0��
        ����֮����ˢ�²������ƣ����Բ�����ʾ����]]
    end
end