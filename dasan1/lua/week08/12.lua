t = {1, 2, 3, 4, 5, 6}

-- function add_(t)
--     local i = 0
--     local sum = 0
--     return function ()
--         i = i + 1
--         if t[i] == nil then
--             return nil
--         end
--         sum = sum + t[i]
--         return sum
--     end
-- end

-- for i in add_(t) do
--     print(i)
-- end

function add(...)
    local sum = 0
    for k, v in ipairs{...} do
        sum = sum + v
    end
    return sum
end

print(add(unpack(t)))