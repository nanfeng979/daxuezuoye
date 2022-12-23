WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua 游戏"
enimyImage      =   -1  --敌机ID
mapImage        =   -1  --背景ID
mapOffset       =   {x=64,y=64} --地图偏移信息
mainTimer       =   -1  --主定时器
rollingDirection=   -1  --地图滚动方向

function Initialize()
    mainTimer = InitTimer(12)
    return 0
end

function LoadImages()
    enimyImage = LoadImage("res\\ENEMY.bmp") --加载图片
    SetColorKey(enemyImage,RGB(0,0,0))  --过滤背景(黑)色
    mapImage = LoadImage("res\\MAP2.bmp")
    
    DisableKeyDelay() --禁止按键延迟
    return 0
end

function HandleFrame()
    DrawMap() --绘制游戏背景
    PaintImage(enemyImage,100,100) --绘制敌机
    TextOut("学号+姓名",200,500,RGB(255,255,255))   
    Show()--显示画布  
    return 0
end

function Terminate()
    return 0
end

function DrawMap()
    -- WSAD--1234
    if GetKeyState(DIK_W) then rollingDirection = 1 end --向上
    if GetKeyState(DIK_S) then rollingDirection = 2 end --向下
    if GetKeyState(DIK_A) then rollingDirection = 3 end --向左
    if GetKeyState(DIK_D) then rollingDirection = 4 end --向右

    --每12毫秒更新一次地图偏移
    if GetTimerState(mainTimer) then
        if rollingDirection == 2 or rollingDirection == 1 then  --垂直方向
            mapOffset.y = mapOffset.y - 1   --纵向偏移量减1             
            if mapOffset.y <= 0 then
                mapOffset.y = 64
            end
        end
        if rollingDirection == 3 or rollingDirection == 4 then  --水平方向
		    mapOffset.x = mapOffset.x -1    --横向偏移量减1
            if mapOffset.x <= 0 then
                mapOffset.x = 64
            end
        end
    end
    
    --背景素材根据地图滚动方向，从指定偏移位置开始铺满窗口
    for x = 0,WINDOW_WIDTH/64 + 1 do
        for y = 0,WINDOW_HEIGHT/64 + 1 do
            if rollingDirection == 1 then  --向上
                StretchPaintImage(mapImage,
                64*x, 64*y+mapOffset.y-64 ,64,64,
                0,0,0,0)
            end
           	if rollingDirection == 2 then  --向下
                StretchPaintImage(mapImage,
                64*x, 64*y-mapOffset.y ,64,64,
                0,0,0,0)
            end
		    if rollingDirection == 3 then  --向左
                StretchPaintImage(mapImage,
                64*x+mapOffset.x-64, 64*y ,64,64,
				0,0,0,0)
            end
            if rollingDirection == 4 then  --向右
                StretchPaintImage(mapImage,
                64*x-mapOffset.x, 64*y ,64,64,
                0,0,0,0)
           end
        end
    end
    
end
