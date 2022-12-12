#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 定义背包的最大容量
const int MAX_SIZE = 150;
// 物品的数量
const int N = 7;

// 物品的体积
int w[N] = {35, 30, 60, 50, 40, 10, 25};
// 物品的价值
int v[N] = {10, 49, 30, 50, 35, 40, 30};

// 初始化dp数组
int dp[N+1][MAX_SIZE+1];

int main()
{
    // 求解背包问题
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= MAX_SIZE; j++)
        {
            if (j < w[i-1])
            {
                // 当前背包容量不足以放入第i个物品，只能选择不放入
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                // 当前背包容量足以放入第i个物品，需要比较放入和不放入的最大价值
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i-1]] + v[i-1]);
            }
        }
    }

    // 输出结果
    cout << "最大价值: " << dp[N][MAX_SIZE] << endl;
    return 0;
}