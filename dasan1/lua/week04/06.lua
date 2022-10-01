users={
    ["tom@hotmail.com"]={Name="tom",Point=1200},
    ["supperman@hotmail.com"]={Name="SupperMan",Point=8800},
    ["John@hotmail.com"]={Name="John",Point=1},
    ["Sam@hotmail.com"]={Name="Sam",Point=2},
    ["Karen@hotmail.com"]={Name="Karen",Point=3},
    ["Bobbie@hotmail.com"]={Name="Bobbie",Point=4},
    ["Jennie@hotmail.com"]={Name="Jennie",Point=5},
    ["Ricardo@hotmail.com"]={Name="Ricardo",Point=6},
    ["Frank@hotmail.com"]={Name="Frank",Point=7},
    ["Christa@hotmail.com"]={Name="Christa",Point=8},
    ["Jimmie@hotmail.com"]={Name="Jimmie",Point=9},
    ["Alfred@hotmail.com"]={Name="Alfred",Point=10},
    ["James@hotmail.com"]={Name="James",Point=11},
    ["Robert@hotmail.com"]={Name="Robert",Point=12},
    ["June@hotmail.com"]={Name="June",Point=13},
    ["Mildred@hotmail.com"]={Name="Mildred",Point=14},
    ["Henry@hotmail.com"]={Name="Henry",Point=15},
    ["Michael@hotmail.com"]={Name="Michael",Point=16},
    ["Scott@hotmail.com"]={Name="Scott",Point=17},
    ["Mickey@hotmail.com"]={Name="Mickey",Point=18},
    ["Roger@hotmail.com"]={Name="Roger",Point=19},
    ["Leticia@hotmail.com"]={Name="Leticia",Point=20},
}

all_player_point = 0 -- 所有玩家的总点数
max_point_player = {Name = "", Point = 0} -- 点数最高的玩家的名字及其点数
min_point_player = {Number = "", Point = 0} -- 点数最低的玩家的名字及其点数

for k, v in pairs(users) do
    -- 点数累加
    all_player_point = all_player_point + v.Point

    -- 判断点数最高的玩家
    if v.Point > max_point_player.Point then
        max_point_player.Point = v.Point
        max_point_player.Name = v.Name
    end

    -- 判断点数最低的玩家
    if min_point_player.Number == "" then
        min_point_player.Number = k
        min_point_player.Point = v.Point
    end
    if v.Point <= min_point_player.Point then
        min_point_player.Point = v.Point
        min_point_player.Number = k
    end
end

print("所有玩家的总点数为：" .. all_player_point)
print("点数最高的玩家的名字及其点数：" .. max_point_player.Name, max_point_player.Point)
print("点数最低的玩家的帐号及其点数：" .. min_point_player.Number, min_point_player.Point)