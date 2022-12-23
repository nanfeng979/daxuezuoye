#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int dp[N][N];

int main() {
    int a, b;
    cout << "shuru a lie:" << " ";
    cin >> a;
    cout << "shuru b hang" << " ";
    cin >> b;

    // 初始化 dp 数组
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            dp[i][j] = 1e9;
        }
    }
    dp[1][1] = 0;  // 两个数都为 1 时

    // 枚举所有可能的状态
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            // 更新 dp 值
            dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
            dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
        }
    }

    // 输出最少操作次数
    cout << dp[a][b] << endl;

    return 0;
}