#include <iostream>

using namespace std;

struct Item
{
    string name;
    int weight;
    int value;
};

const int N = 7;
const int C = 150;
int f[N + 1][C + 1];

Item items[N] = {{"A", 35, 10}, {"B", 30, 49}, {"C", 80, 70}, {"D", 50, 50}, {"E", 40, 35}, {"F", 10, 40}, {"G", 25, 30}};

int main()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= C; j++)
        {
            // 不把第i个物品放入背包
            f[i][j] = f[i - 1][j];
            // 把第i个物品放入背包
            if (j > items[i - 1].weight)
                f[i][j] = max(f[i][j], f[i - 1][j - items[i - 1].weight] + items[i - 1].value);
        }
    }

    cout << "最大价值为: " << f[N][C] << endl;
    return 0;
}