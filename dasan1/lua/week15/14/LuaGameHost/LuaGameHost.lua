WINDOW_WIDTH    =   800
WINDOW_HEIGHT   =   600
BPP             =   16
FULLSCREEN		=   false
GAME_TITLE      =   "2220631136余庆祥游戏"
enemyImage      =   -1 -- 敌人
playerShow      =   false -- 判断玩家是否显示

function Initialize()
    bgMusic = LoadMIDI("res/a.mid") -- 背景音乐
    DisableKeyDelay() -- 禁止键盘延迟，键盘输入必要
    return 0
end

function LoadImages()
    playerImage = LoadImage("res/plane_center.BMP") -- 加载玩家图片资源
    SetColorKey(playerImage, RGB(0, 0, 0)) -- 将玩家的黑色像素设置为透明

    enemyImage = LoadImage("res/ENEMY.bmp") -- 加载敌人图片资源
    SetColorKey(enemyImage, RGB(0, 0, 0)) -- 将敌人的黑色像素设置为透明
    
    deadImage = LoadImage("res/dead.BMP") -- 加载死亡动画资源
    SetColorKey(deadImage, RGB(0, 0, 0)) -- 将死亡动画的黑色像素设置为透明
   
    return 0
end

function HandleFrame()
    FillRectangle(RGB(0, 255, 0), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) -- 绿色背景
    
    PaintImage(enemyImage, 100, 100) -- 绘制敌人
    if playerShow then
        PaintImage(playerImage, 100, 400) -- 绘制玩家
    end
    
    PaintImage(deadImage, 250, 100) -- 绘制死亡动画
    deadN = 4 -- 单独绘制第N帧
    StretchPaintImage(deadImage, 250 + (deadN - 1) * 66, 300, 66, 66, 66 * (deadN - 1), 0, 66, 66) -- 绘制死亡动画的某一帧
    
    TextOut("2220631136+余庆祥", 200, 500, RGB(0, 0, 255))
    
    -- 播放背景音乐
    if not GetMIDIStatus(bgMusic) then
        PlayMIDI(bgMusic)
    end
    
    -- 按下alt后按enter键
    if GetKeyState(DIK_LMENU) then 
        if GetKeyAction(DIK_RETURN, true) then
            ToggleScreenMode() -- 全屏
        end
    end
    
    -- 鼠标左键点击
    if GetMouseButtonState(0) then
        playerShow = true
    end
    
    Show()
    
    return 0
end

function Terminate()
    return 0
end


