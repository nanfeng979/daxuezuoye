WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "Lua 游戏"
enimyImage      =   -1  --敌机ID
mapImage        =   -1  --背景ID
mapOffset       =   {x=64,y=64} --地图偏移信息
mainTimer       =   -1  --主定时器

function Initialize()
    mainTimer = InitTimer(12)   --12毫秒
    return 0
end

function LoadImages()
    enimyImage = LoadImage("res\\ENEMY.bmp") --加载敌机图片
    SetColorKey(enemyImage,RGB(0,0,0))  --过滤敌机背景(黑)色

    mapImage = LoadImage("res\\MAP2.bmp")      --加载背景图片

    return 0
end

function HandleFrame()
    DrawMap() --绘制游戏背景
    DrawString()

    Show()--显示画布
    return 0
end

function Terminate()
    return 0
end


function DrawMap()
    if GetTimerState(mainTimer) then
        mapOffset.y = mapOffset.y - 1       --向下滚动
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
    TextOut("学号+姓名",300,300,RGB(255,255,255)) --在适当位置显示你的个人信息
end
