#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 检查给定的数字排列是否符合条件
bool check(const string& s, int n) {
// 将排列中的前五个数字转换为整数并记为a
int a = stoi(s.substr(0, 5));

// 将排列中的后五个数字转换为整数并记为b
int b = stoi(s.substr(5, 5));

// 计算a / b的值
return a / b == n;
}

int main() {
    // 输入n的值
    int n;
    // cin >> n;
    n = 8;

    // 枚举所有可能的数字排列
    for (int i = 0; i < 100000; i++) {
    // 将i转换为字符串
    string s = to_string(i);

    // 将字符串左侧补0
    s = string(5 - s.size(), '0') + s;

    // 如果排列符合条件，输出表达式并换行
    if (check(s, n)) {
    cout << s.substr(0, 5) << " / " << s.substr(5, 5) << " = " << n << endl;
    }
    }

    return 0;
}