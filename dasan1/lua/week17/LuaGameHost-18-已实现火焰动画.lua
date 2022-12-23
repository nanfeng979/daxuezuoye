WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua ��Ϸ"

--��Ϸ״̬
GAME_LOG	    =   0           --��ӭ����
GAME_START	    =   1           --��Ϸ�ѿ�ʼ
GAME_OVER	    =   2           --��Ϸ�ѽ���

gameStatus      =   GAME_LOG	--��Ϸ״̬

mapOffset         =   {x=64,y=64} --��ͼƫ����Ϣ
mapImage        =   -1          --������ͼ
mainTimer        =   -1   --����ʱ��
moveSpeed       =   2                    --���ڵ��������ٶ�
plane       =   {   
                    x=0,                            --�һ�λ��:x����
                    y=0,                            --�һ�λ��:y����
                    status=2,                   --�һ���̬  1 2 3���� �� ��
                    canControl=false,    --�һ��Ƿ��ܿ���
                    superMode=false,    --�һ��Ƿ��޵�
                    dead    = true,           --�һ��Ƿ�������
                    remain  =   3,            --�һ�ʣ������
                    superModeTimer = -1,    --�޵�ʱ�䶨ʱ��
                    flashTimer  = -1               --�޵�ʱ,��˸��ʱ��
                }
planeImages     =   {}          --�ɻ�ͼƬ��Դ

ENEMY_NUMBER      =   26	    --�л�����
enemies                     =   {}       --�л���Ϣ,����,
            --ÿ��Ԫ��Ϊһ��table��{x,y,speed,direction,style,dead}
enemyLostCount       =   0         --�л�����������
ballImage                  =   -1        --�л��ӵ�ͼƬ��Դ
enemyImage             =   -1        --�л�ͼƬ��Դ

BULLET_NUMBER   =   20	        --�ӵ�����
leftBullets     =   {}          --����ӵ���Ϣ,����,{x,y}
rightBullets    =   {}          --�Ҳ��ӵ���Ϣ,����,{x,y}
bullet          =   {           --�ӵ�������Ϣ
                        timer=-1,   --���䶨ʱ��
                        number=1    --��ǰ�ӵ����
                    }   
buletImages     =   {}          --�ӵ�ͼƬ��Դ(����)

--�һ�������Ϣ
deadFlame       =   {x=0,y=0,frame=0,timer=0}   
enemyFlames     =   {}      --�л�������Ϣ,����,
                            --{x=0,y=0,frame=0,timer}
deadImage       =   -1      --�һ�ײ�ٻ���ͼƬ��Դ
enemyDeadImage  =   -1      --�л�ײ�ٻ���ͼƬ��Դ

function Initialize()
    mainTimer     = InitTimer(12)
    --��ʼ���л����ӵ������Ǵ���������Ч״̬
    for i=1,ENEMY_NUMBER do
        enemies[i]  = {x=0,y=0,speed=0,dead=true,direction=0,style=0}  
    end
    DisableKeyDelay()       --��ֹ�����ӳ�
    --��ʼ�����ӵ�������
    for i = 1,BULLET_NUMBER do
        leftBullets[i] =  {x = -100, y = -100}
        rightBullets[i] = {x = -100, y = -100}
    end
    --��ʼ���ӵ����䶨ʱ����ÿ�� 0.1 �뷢��һ���ӵ�
    bullet.timer     = InitTimer(100)   
    
    --��ʼ���л�������Ϣ
    for i = 1,ENEMY_NUMBER do
        enemyFlames[i] = {  x=0,
                            y=0,
                            frame=0,
                            timer=InitTimer(150)}
    end
    --��ʼ���һ�����������ʱ��
    deadFlame.timer = InitTimer(200)
    
    return 0
end

function LoadImages()
    mapImage        =   LoadImage("res\\map2.bmp")
    planeImages[1]  =   LoadImage("res\\plane_left.BMP")
    SetColorKey(planeImages[1],RGB(0,0,0))
    planeImages[2]  =   LoadImage("res\\plane_center.BMP")
    SetColorKey(planeImages[2],RGB(0,0,0))
    planeImages[3]  =   LoadImage("res\\plane_right.BMP")
    SetColorKey(planeImages[3],RGB(0,0,0))
    ballImage       =   LoadImage("res\\ball.bmp")
    SetColorKey(ballImage,RGB(0,0,0))
    enemyImage        =   LoadImage("res\\enemy.bmp")
    SetColorKey(enemyImage,RGB(0,0,0))
    buletImages[1]  =   LoadImage("res\\bullet_left.BMP")
    SetColorKey(buletImages[1],RGB(0,0,0))
    buletImages[2]  =   LoadImage("res\\bullet_right.BMP")
    SetColorKey(buletImages[2],RGB(0,0,0))
          
    enemyDeadImage   =   LoadImage("res\\flame.bmp")
    SetColorKey(enemyDeadImage,RGB(0,0,0))
    deadImage        =   LoadImage("res\\dead.bmp")
    SetColorKey(deadImage,RGB(0,0,0))

     return 0
end

function HandleFrame()
     --��������
    if 0 ~= ProcessInput() then 
        return 1        --���ط� 0 ֵ����Ϸ�˳�
    end
    CheckHit() --��ײ���  
    EndTest()  --�������
    DrawMap()    
    DrawEnemy()
    DrawPlane()
    DrawBullet()
    DrawFlame()--���ƻ���
    DrawString()
    
    Show()
    return 0
end

function Terminate()
    return 0
end

function DrawBullet()
    for i = 1,BULLET_NUMBER do
        PaintImage(buletImages[1], 
                leftBullets[i].x, leftBullets[i].y)
        PaintImage(buletImages[2], 
                rightBullets[i].x, rightBullets[i].y)
    
        if GetTimerState(mainTimer) then
            leftBullets[i].x = leftBullets[i].x - 1
            --û�������ӵ�y==0�������������ߣ�������ʾ����
            leftBullets[i].y = leftBullets[i].y - 12    
            
            rightBullets[i].x = rightBullets[i].x + 1
            rightBullets[i].y = rightBullets[i].y - 12
        end
    end    
end
function DrawPlane()
    ---[[
    if gameStatus ~= GAME_START then
        return 
    end
    --]]
    if plane.dead then
        plane.remain = plane.remain - 1   --ʣ��ɻ�����һ
        plane.dead  = false                                 --��һ�ܷɻ�����
        plane.superMode = true                        --�޵�ģʽ
        plane.canControl = false                       --��ʼʱ���ܿ���
        plane.x = WINDOW_WIDTH/2 - 25    --�һ��ӵײ��м�λ�ÿ�ʼ����
        plane.y = WINDOW_HEIGHT
        plane.superModeTimer = InitTimer(3000)    --�޵�ʱ��3��
        plane.flashTimer = InitTimer(30)                    --��ʱ30���룬
        --��ÿ��30����Ż�һ���һ���������˸������ʱ�Ƚ�ƽ�����������˸
    end
    
  
    if not plane.canControl then
        if plane.y > WINDOW_HEIGHT - 100 then         
            --�ɻ��ճ���ʱ���޷����Ƶ�
            if GetTimerState(mainTimer) then
                plane.y = plane.y - moveSpeed --�Զ�����
                plane.status = 2
            end
        else
            plane.canControl = true
        end
    end
    
    if plane.superMode then
        if GetTimerState(plane.superModeTimer) then 
            --�޵�ʱ���ѹ���
            ClearTimer(plane.superModeTimer)
            ClearTimer(plane.flashTimer)
            plane.superMode = false
        end
        --�޵�ʱ����˸Ч��
        --��ʱ30����,������˸��
        --��ÿ��30����Ż�һ���һ�,����ʱ�Ƚ�ƽ�����������˸
        if not GetTimerState(plane.flashTimer) then       
            return 
        end
    end
    
    PaintImage(planeImages[plane.status],plane.x,plane.y)
end

function DrawEnemy()
    for _ , e in ipairs(enemies) do
        if not e.dead  then             --����л�δ�٣����ӵ���Ч
            if e.style == 1 then        --�л�
                PaintImage(enemyImage,e.x,e.y)
            elseif e.style == 2 then    --�ӵ�
                PaintImage(ballImage,e.x,e.y)
            end
            if GetTimerState(mainTimer) then
               --��ֱ�½��ٶ�e.speed=2~5 ,movespeed=2~5 ���ڵ��������ٶ�
                e.y = e.y + e.speed + (moveSpeed-2)     
                --ˮƽ�ƶ�����e.direction =-1 ~ 1 (�� �� ��)
                e.x = e.x + e.direction 
            end
        end
        --�л��ܳ����׻�������������
        if e.y > WINDOW_HEIGHT or e.dead  then      
            e.x = GetRandomNumber(35,WINDOW_WIDTH - 35)
            e.y = GetRandomNumber(-35,0)
            e.speed = GetRandomNumber(2,5)          --/2-5���½��ٶ�
            e.direction = GetRandomNumber(-1,1)    -- -1,0,1  �����ƶ�����
            e.style = GetRandomNumber(1,2)            -- �л�1���ӵ�2
            
            e.dead  = false                                 --���˸���
        end
    end
end

function DrawMap()
    if GetTimerState(mainTimer) then
        mapOffset.y = mapOffset.y - 1               --�¾�

        if mapOffset.y <= 0 then  
            mapOffset.y = 64
        end
        --���ݷɻ���״̬������ͼ������Ҿ���Ч��
        mapOffset.x = mapOffset.x + plane.status - 2 
        if mapOffset.x <=0 then 
            mapOffset.x = 64
        end
        
        if mapOffset.x >64 then
            mapOffset.x = 1
        end
   end

    
    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            StretchPaintImage(mapImage,64*x-mapOffset.x, 64*y-mapOffset.y,64,64,0,0,0,0)
        end
    end
end


function DrawString()
    local x = (WINDOW_WIDTH - 140)/2
    local red = RGB(255,0,0)
    local blue = RGB(0,0,255)
    
    if gameStatus == GAME_LOG then      --��ӭ����
        TextOut("����ս��",             x,170,red)
        TextOut("��  ��: Ctr",          x,240,blue)
        TextOut("ը  ��: Space",        x,260,blue)
        TextOut("��  ��:   +",          x,280,blue)
        TextOut("��  ��:   -",          x,300,blue)
        TextOut("��  ͼ: Return",       x,320,blue)
        TextOut("��  ��: Esc",          x,340,blue)
        TextOut("ȫ��/����: ALT+ENTER", x,360,blue)
    
        PaintImage(planeImages[2],x-90,150)
        PaintImage(planeImages[2],x+180,150)
    end
    
    if gameStatus == GAME_START then        --��Ϸ������
        --����ʣ��ɻ�
        for i=1,plane.remain do
            StretchPaintImage(planeImages[2],
                    10+(i-1)*25,WINDOW_HEIGHT - 30,20,20,
                    0,0,0,0)
        end
        TextOut("ʣ��ɻ�:" .. plane.remain,
                    10,WINDOW_HEIGHT - 50,blue)
        --���Ƶл���������ĵл�������
        StretchPaintImage(enemyImage,
                WINDOW_WIDTH - 60, WINDOW_HEIGHT - 30,20,20,
                0,0,0,0)
        TextOut(enemyLostCount .. "",
                WINDOW_WIDTH-35, WINDOW_HEIGHT-25,red)
        TextOut("�÷�" .. enemyLostCount * 50,
                WINDOW_WIDTH/2-40, 5, blue)
    end
    
    if gameStatus == GAME_OVER then
        TextOut("Game Over",                                  
                x, WINDOW_HEIGHT/2-80, red)
        TextOut("������л� " .. enemyLostCount .. " ��",
                x, WINDOW_HEIGHT/2-30, blue)
        TextOut("���س�������",                               
                x, WINDOW_HEIGHT/2, blue)
        TextOut("����ս��: Lua ��Ϸ!!!",                      
                x, WINDOW_HEIGHT/2+50, blue)
    end    
end

function ProcessInput()    
    --��ⷢ���ӵ�
    if gameStatus == GAME_START and 
        plane.canControl == true then
        --��Control�����£�ÿ��0.1 �뷢��һ��
        if GetKeyState(DIK_LCONTROL) and 
            GetTimerState(bullet.timer) then  
            leftBullets[bullet.number].x = plane.x + 13
            leftBullets[bullet.number].y = plane.y
            rightBullets[bullet.number].x = plane.x + 32
            rightBullets[bullet.number].y = plane.y
            
            bullet.number = bullet.number + 1
            if bullet.number == BULLET_NUMBER then
                bullet.number  = 1
            end
        end
    end    
    
    --��ⷽ������ƶ��һ�
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
            plane.status = 1  --���Ʒɻ�ͼ��
        end
		if GetKeyState(DIK_RIGHT)	then    
            plane.x=plane.x+moveSpeed  
            plane.status = 3  --���Ʒɻ�ͼ��
        end 

		--��Χ��飬��ֹ�����߽�
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
    end
    --������ɿ����ָ��ɻ���״̬
    if GetKeyAction(DIK_UP,false) or
       GetKeyAction(DIK_DOWN,false) or
       GetKeyAction(DIK_LEFT,false) or
       GetKeyAction(DIK_RIGHT,false) then
            plane.status = 2 
    end

    --��Ϸ�ٶȿ���
    if GetKeyAction(DIK_ADD,false)then        --����
        moveSpeed = moveSpeed + 1
		if moveSpeed>5 then moveSpeed=5  end
    end
    
    if GetKeyAction(DIK_SUBTRACT,false) then   --����
        moveSpeed = moveSpeed - 1
		if moveSpeed<2 then moveSpeed=2  end
    end
    
    if GetKeyState(DIK_LMENU) and 
       GetKeyAction(DIK_RETURN,false) then
       -- ��ALT + Enter �л���Ļģʽ
        ToggleScreenMode()           
    elseif gameStatus ~= GAME_START then 
        if GetKeyAction(DIK_RETURN,false) then --��ʼ��Ϸ
            --��ʼ��Ϸ�����г�ʼ��      
			for k = 1, ENEMY_NUMBER do
			    --���ел����ӵ����Ǵ���������Ч״̬
				enemies[k].dead=true  
			end
			enemyLostCount=0
			plane.dead = true
			plane.remain=3
			gameStatus=GAME_START
			moveSpeed=2
		end
    end
    
    if GetKeyState(DIK_ESCAPE) then     --�˳�
        return 1
    end
    
    return 0
end

function CheckHit()
    --��Ϸ���ڽ�����
    if gameStatus ~= GAME_START then        
        return
    end
    --1�����л��Ƿ񱻻���
    for i, e in ipairs(enemies) do
        --����δ��
        if not e.dead then        
            if e.style == 2 then       --�ӵ�
                --�ӵ�������ײ���
            elseif e.style == 1 and 
                  not OutOfRange(e.x, e.y) then    
                  --�л��������ڴ�����
                for b = 1,BULLET_NUMBER do          
                    --�������ӵ�����ײ���
                    --������ӵ��Ƿ�����˸õл�
                    BulletHitEnemy(leftBullets[b],i)
                    --������ӵ��Ƿ�����˸õл�
                    BulletHitEnemy(rightBullets[b],i)
                end
            end
        end
    end
    --2 ����һ��Ƿ�ײ��
    --��Ϊ�޵�״̬�����
    if not plane.superMode then   
        for _, e in ipairs(enemies) do
            --�ӵ���л�δ������Ч�������ڴ�����        
            if e.dead ~= 0 and 
                not OutOfRange(e.x,e.y) then    
                if e.style == 2   then     --�ӵ�
                    --����һ���з��ӵ�����ײ
                    BallHitPlane(e)
                elseif e.style == 1 then   --�л�
                    --����һ���л�����ײ
                    EnemyHitPlane(e)
                end
            end
        end
    end
end

-- �����Ƿ񳬳���Ļ��Χ?
function OutOfRange(x,y)    
    if x<35 or x>WINDOW_WIDTH - 35 or 
       y<35 or y>WINDOW_HEIGHT - 35 then
		return true
	else
		return false
	end
end

--�����һ��ӵ���л�����ײ
--b: �ӵ�
--i: �л�֮����
function BulletHitEnemy(b, i)
    local e = enemies[i]    --�л�
    if not OutOfRange(b.x,b.y) then
         if IntersectRect(e.x+7,e.y+3,22,26,
                          b.x,b.y,5,13) then
            e.dead = true     --�л�����
            --����ĵл�������1
            enemyLostCount  = enemyLostCount + 1       
            b.y=0             --ʹ�ӵ���ʧ            
            --���û������꣬����ȷɻ���,
            --Ϊʹ����������ɻ����Ķ���
            --x��������10���㣬y��������8����
            enemyFlames[i].x     =e.x-10
            enemyFlames[i].y     =e.y-8   
            --����״̬����Ϊ1���������涯��            
            enemyFlames[i].frame = 1      
        end
   end
end

--����л��ӵ����һ�����ײ
function BallHitPlane(e)
     if IntersectRect(e.x,e.y,8,8,
                plane.x+14,plane.y+16,23,41) then         
        e.dead  = true       --�ӵ���Ч
        plane.dead = true --�һ�����
        --���û������꣬������ӵ���,
        --Ϊʹ�����������ӵ����Ķ���
        --x��������29���㣬y��������29����
        deadFlame.x = e.x - 29 
        deadFlame.y = e.y - 29
        --����״̬����Ϊ1���������涯��            
        deadFlame.frame = 1
    end
end

--����л����һ�����ײ
function EnemyHitPlane(e)
    if IntersectRect(e.x+7,e.y+3,22,26,
                plane.x+14,plane.y+16,23,41) then       
        e.dead  = true    --�л�����
        plane.dead = true --�һ�����
        --���û�����ȷλ�ã��Եл�Ϊ���ģ�����ȵл���
        --Ϊʹ�����������ӵ����Ķ���
        --x��������15���㣬y��������15���� 
        deadFlame.x = e.x - 15 
        deadFlame.y = e.y - 15
        --����״̬����Ϊ1���������涯��         
        deadFlame.frame = 1      
     end
end

--�������
function EndTest()
    if plane.remain == -1  then --��Ϸ����
		gameStatus=GAME_OVER
	end
end

--������������
function DrawFlame() 
    --�л���������
    for _,ef in ipairs(enemyFlames) do
        if ef.frame ~= 0 then   --����������
            StretchPaintImage(enemyDeadImage, 
                       ef.x,ef.y,54,50,
                       (ef.frame - 1)*54,0,54,50)
            -- 150 ���������֡
            if GetTimerState(ef.timer) then     
                ef.frame = ef.frame + 1
                if ef.frame == 11 then
                    ef.frame = 0 --����ֹͣ����
                end
            end
        end
    end
    --�һ���������
    if deadFlame.frame ~= 0 then    --����������
        StretchPaintImage(deadImage,
               deadFlame.x,deadFlame.y,66,66,
               (deadFlame.frame - 1) * 66,0,66,66)
        if GetTimerState(deadFlame.timer) then
            deadFlame.frame = deadFlame.frame + 1
            if deadFlame.frame == 9 then
                deadFlame.frame = 0 --����ֹͣ����
            end
        end
    end
end

