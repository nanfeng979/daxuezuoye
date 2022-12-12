WINDOW_WIDTH    =   640
WINDOW_HEIGHT   =   480
BPP             			 =   16
FULLSCREEN				 =   false
GAME_TITLE      	    =   "Lua сно╥"

function Initialize()
    return planeInitialize()
    --return 0
end

function LoadImages()
    return planeLoadImages()
    --return 0
end

function HandleFrame()
    return planeHandleFrame()
    --return 0
end

function Terminate()

    return 0
end

--dofile "plane.lua"
--dofile "plane.luac"
dofile "plane_NOSound.luac"
