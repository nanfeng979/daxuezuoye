-- t={10,20,30}
-- for element in values(t) do
--     print(element)
-- end	

t = {10, 20, 30}

function next(t, i)
    i = i + 1
    if t[i] then
        return i, t[i]
    end
end
function values(t)
    return next, t, 0
end

print("无状态迭代器：")
for k, v in values(t) do
    print(k, v)
end


function iter(state)
    state.i = state.i + 1
    if state.t[state.i] then
        return state.i, state.t[state.i]
    end
end

function values(a)
    return iter, {t = a, i = 0}
end

print("复杂状态迭代器：")
for i, v in values(t) do
    print(i,v)
end


function ipairs(t, f)
    local i = 0
    i = i + 1 
    while t[i] do
          f(i)
          i = i + 1
    end
end

print("真正迭代器：")
ipairs(t, function(i)
    print(i, t[i])
end)




