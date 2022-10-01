function solve(a, b, c)
    local q = b ^ 2 - 4 * a *c
    if q < 0 then
        return 0, nil, nil
    elseif q == 0 then
        local answer = -b / (2 * a)
        return 1, answer, answer
    else
    return 2, (-b + math.sqrt(q)) / (2 * a), (-b - math.sqrt(q)) / (2 * a)
    end
end

print(solve(2, -7, 3))