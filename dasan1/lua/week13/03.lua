print ("����任����...")
t1 = {1,2,3,4,5}
f = function(v) --��1������Ԫ��Ϊ����
	return v * 10 --���ر任���1��ֵ
end

print("�任ǰ������Ϊ:")
for i,v in ipairs(t1) do
	print(v)
end

 arrayTransformation(t1,f) --��C�ṩ

 print("�任�������Ϊ:")
for i,v in ipairs(t1) do
	print(v)
end

 print("======================================")


print("׼������ƽ�������ԣ����ڳ�ʼ������...")
s = os.time()
t2={ }
for i=1,10000000 do
	t2[i] = i
end
print("��ʼ����ʱ��" .. os.time()-s .."��")
s = os.time()

print(avege(t2)) --��C�ṩ
print("AVG������ʱ��"..os.time()-s .."��")

print("======================================")

s = os.time()
print(avegeraw(t2)) --��C�ṩ
print("AVGRAW������ʱ��"..os.time()-s .."��")


print("======================================")
print("�ַ����ָ����...")
s = "The quick brown fox jumps over the lazy dog"
print("�����ַ���Ϊ:" .. s)
t = split(s, " ") --��C�ṩ
print("�ָ���Ϊ:")
for i,v in ipairs(t) do
    print(v)
end


print("======================================")
print("ת���ַ���Ϊ��д:")
print(upper(s)) --��C�ṩ

print("======================================")
s2= "LUA"
print("ת���ַ���ΪСд:")
print(lower(s2)) --��C�ṩ