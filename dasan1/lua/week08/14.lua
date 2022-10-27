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


function my_pairs(t)
    local k
    return function ()
        k = next(t, k)
        if k ~= nil then
            while t[k].Point < 15 do
                k = next(t, k)
                if k == nil then
                    return nil
                end
            end
            return next(t, k)
        end
    end
end

print("使用闭包:")
for k, v in my_pairs(users) do
    print(k, v.Name, v.Point)
end


function iter(t, i)
    i = next(t, i)
    if t[i] then
        while t[i].Point < 15 do
            i = next(t, i)
            if i == nil then
                return nil
            end
        end
        return i, t[i]
    end
end

function my_pairs(t)
    return iter, t, next(t)
end

print("使用无状态迭代器代码:")
for k, v in my_pairs(users) do
    print(k, v.Name, v.Point)
end


function iter(state)
    if state.t[state.i] then
        state.i = next(state.t, state.i)
        while state.t[state.i].Point < 15 do
            state.i = next(state.t, state.i)
            if state.i == nil then
                return nil
            end
        end
        return state.i, state.t[state.i]
    end
end

function my_pairs(param_t)
    return iter, {t = param_t, i = next(param_t)}
end

print("使用table作为恒定状态的复杂状态迭代器:")
for k, v in my_pairs(users) do
    print(k, v.Name, v.Point)
end


function my_pairs(t, f)
    local i = next(t)
    while t[i] do
        while t[i].Point < 15 do
            i = next(t, i)
            if i == nil then
                return nil
            end
        end
        f(i)
        i = next(t, i)
    end
end

print("真正迭代器：")
my_pairs(users, function(i)
    print(i, users[i].Name, users[i].Point)
end)