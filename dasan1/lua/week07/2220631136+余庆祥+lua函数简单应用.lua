local function getRandom()
    local random = math.random() * 1000000
    return (random - (random % 1)) % 3 + 1
end

local function game()
    local player
    local player_win = 0
    local computer
    local computer_win = 0
    local draw = 0
    local invalid_input = 0
    local count = 0
    local numberToString = {"scissors", "stone", "paper"}

    while true do
        print("-----------------------------------------------")
        print("Please input a number 1~4(1.scissors, 2.stone, 3.paper, 4.quit): ")

        player = io.read()

        if player == "1" or player == "2" or player == "3" or player == "4" then
            player = tonumber(player)

            if player == 4 then
                print("play " .. count .. " times, computer win:" .. computer_win
                        .. ", you win:" .. player_win .. ", draw:" .. draw .. 
                        ", invalid input:" .. invalid_input) -- 结束时输出的内容
                break
            end

            computer = getRandom()
            print(computer)

            if player == computer then -- 平局时
                draw = draw + 1
                print("draw")
            elseif player == 1 then -- 玩家输入1时
                if computer == 2 then
                    computer_win = computer_win + 1
                    print("computer win")
                elseif computer == 3 then
                    player_win = player_win + 1
                    print("you win")
                end
            elseif player == 2 then -- 玩家输入2时
                if computer == 3 then
                    computer_win = computer_win + 1
                    print("computer win")
                elseif computer == 1 then
                    player_win = player_win + 1
                    print("you win")
                end
            elseif player == 3 then -- 玩家输入3时
                if computer == 1 then
                    computer_win = computer_win + 1
                    print("computer win")
                elseif computer == 2 then
                    player_win = player_win + 1
                    print("you win")
                end
            end

            print("")
            print("you:" .. numberToString[player])
            print("computer:" .. numberToString[computer])
        else
            invalid_input = invalid_input + 1 -- 异常输入时
            print("Invalid number")
        end

        count = count + 1 -- 每次输入计数一次
    end
end

local function main()
    math.randomseed(os.time())
    game()
end

main()