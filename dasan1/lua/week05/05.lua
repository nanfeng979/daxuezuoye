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

function highest_point(...)
    local max_account = ""
    local max_name = ""
    local max_point = 0
    for k, v in pairs({...}) do
        if max_point <= users[v].Point then
            max_point = users[v].Point
            max_account = v
        end
    end
    max_name = users[max_account].Name
    
    return max_account, max_name, max_point
end

print("\t点数最高的账号\t\t", "姓名\t", "点数\n",
    highest_point("tom@hotmail.com", "supperman@hotmail.com", 
                "John@hotmail.com", "Sam@hotmail.com"))