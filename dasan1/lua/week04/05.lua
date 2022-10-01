function resolve_equation(a, b, c)
    local i = b^2 - 4*a*c
    if i < 0 then
        return "无解", "无解"
    end
    local n = math.sqrt(i)
    local m = (2 * a)
    local x1 = (-b + n) / m
    local x2 = (-b - n) / m
    return x1, x2
end

x1, x2 = resolve_equation(2, -7, 3)
print("该一元二次方程的解为：" .. x1 .. "、" .. x2)

