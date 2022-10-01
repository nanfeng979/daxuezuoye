max = 36

sum = 0
for i = 1, max do
    sum = sum + i
end
print(sum)

sum = 0
i = 1
while i <= max do
    sum = sum + i
    i = i + 1
end
print(sum)

sum = 0
i = 1
repeat
    sum = sum + i
    i = i + 1
until i > max
print(sum)