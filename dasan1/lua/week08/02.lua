tabLanguage = {
    "Lua",
    "swift",
    "python",
    "java",
    "C",
}

print("元素的默认序列排序的排序前：")
for k, v in pairs(tabLanguage) do
    print(k, v)
end

print("元素的默认序列排序的排序后：")
table.sort(tabLanguage)
for k, v in pairs(tabLanguage) do
    print(k, v)
end

print("按字符由短到长排序：")
table.sort(tabLanguage, function (a, b) return (#a < #b) end)
for k, v in pairs(tabLanguage) do
    print(k, v)
end