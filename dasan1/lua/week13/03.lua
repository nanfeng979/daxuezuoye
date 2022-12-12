print ("数组变换测试...")
t1 = {1,2,3,4,5}
f = function(v) --以1个数组元素为参数
	return v * 10 --返回变换后的1个值
end

print("变换前的数组为:")
for i,v in ipairs(t1) do
	print(v)
end

 arrayTransformation(t1,f) --由C提供

 print("变换后的数组为:")
for i,v in ipairs(t1) do
	print(v)
end

 print("======================================")


print("准备进行平均数测试，正在初始化数组...")
s = os.time()
t2={ }
for i=1,10000000 do
	t2[i] = i
end
print("初始化用时：" .. os.time()-s .."秒")
s = os.time()

print(avege(t2)) --由C提供
print("AVG函数用时："..os.time()-s .."秒")

print("======================================")

s = os.time()
print(avegeraw(t2)) --由C提供
print("AVGRAW函数用时："..os.time()-s .."秒")


print("======================================")
print("字符串分割测试...")
s = "The quick brown fox jumps over the lazy dog"
print("测试字符串为:" .. s)
t = split(s, " ") --由C提供
print("分割结果为:")
for i,v in ipairs(t) do
    print(v)
end


print("======================================")
print("转换字符串为大写:")
print(upper(s)) --由C提供

print("======================================")
s2= "LUA"
print("转换字符串为小写:")
print(lower(s2)) --由C提供