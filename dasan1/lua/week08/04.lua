local function getRandom()
    local random = math.random() * 1000000
    return (random - (random % 1)) % 10 + 1
end

local count = 5
math.randomseed(os.time())
local computer = getRandom()

while count > 0  do
    player = tonumber(io.read())
    if player ~= nil then
        if player > computer then
            print("输入的数太大了")
        elseif player < computer then
            print("输入的数太小了")
        else
            print("恭喜你答对了  " .. player)
            print("猜错" .. 5 - count .. "次，游戏成功")
            break
        end
    end
    count = count - 1
end

if(count == 0) then
    print("猜错5次，游戏失败")
end