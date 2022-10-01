function viewtable(t)
    for k, v in pairs(t) do
        print(k, v)
    end
end

-- viewtable{Name="tom",Point=1200,"hello",123,[-3]="aa"}
--[[
    1       hello
    2       123
    -3      aa
    Name    tom
    Point   1200
]]
-- viewtable({Name="tom",Point=1200,"hello",123,[-3]="aa"})
--[[
    1       hello
    2       123
    -3      aa
    Name    tom
    Point   1200
]]
t = {Name="tom",Point=1200,"hello",123,[-3]="aa"}
-- viewtable t -- 出错
-- viewtable(t)
--[[
    1       hello
    2       123
    -3      aa
    Name    tom
    Point   1200
]]
viewtable{t}
--[[
    1   table: table' s dizhi
]]
