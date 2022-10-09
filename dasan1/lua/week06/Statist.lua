-- 2220631136余庆祥
Statist = {} -- 定义一个名为 Statist 的模块

-- Avg 求平均数
function Statist.Avg(t)
    local sum = 0
    local count = 0
    for k, v in ipairs(t) do
        sum = sum + v
        count = count + 1
    end
    if count == 0 then
        return nil
    end
    return sum / count
end

-- Count 计数
function Statist.Count(t)
    local count = 0
    for k, v in ipairs(t) do
        count = count + 1
    end
    return count
end

-- Sun 求和
function Statist.Sum(t)
    local sum = 0
    local count = 0
    for k, v in ipairs(t) do
        sum = sum + v
        count = count + 1
    end
    if count == 0 then
        return nil
    end
    return sum
end

-- Max 求最大值
function Statist.Max(t)
    local max = nil
    for k, v in ipairs(t) do
        if max then
            if max < v then
                max = v
            end
        else
            max = v
        end
    end
    return max
end

-- Min 求最小值
function Statist.Min(t)
    local min = nil
    for k, v in ipairs(t) do
        if min then
            if min > v then
                min = v
            end
        else
            min = v
        end
    end
    return min
end

-- Varp 求方差
function Statist.Varp(t)
    local count = Statist.Count(t)
    if count == 0 then
        return nil
    end
    local m = Statist.Avg(t)
    local xm = 0
    for k, v in ipairs(t) do
        xm = xm + (v - m) ^ 2
    end
    return (1 / count) * xm
end

-- StdDevP 求标准差
function Statist.StdDevP(t)
    local varp = Statist.Varp(t)
    if varp == nil then
        return nil
    end
    return math.sqrt(varp)
end

-- t = {3, 2, 9, 1, 4, 0, 8}
-- print(Statist.StdDevP(t))

return Statist