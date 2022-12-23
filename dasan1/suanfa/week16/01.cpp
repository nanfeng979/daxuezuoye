#include <iostream>
#include <cstdio>
#include <algorithm>
#include <clocale>
#include <cstdio>

#define N 100

using namespace std;

struct goods {
    int sign;  // 序号
    int weight;  // 重量
    int value;  // 价值
};

int n, bestValue, cv, cw, C;
int X[N], cx[N];
struct goods goods[N];

int KnapSack(int n, struct goods a[], int C, int x[]) {
    int V[N][10 * N];
    for (int i = 0; i <= n; i++)
        V[i][0] = 0;
    for (int j = 0; j <= C; j++)
        V[0][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= C; j++)
            if (j < a[i - 1].weight)
                V[i][j] = V[i - 1][j];
            else
                V[i][j] = max(V[i - 1][j], V[i - 1][j - a[i - 1].weight] + a[i - 1].value);

    for (int i = n, j = C; i > 0; i--) {
        if (V[i][j] > V[i - 1][j]) {
            x[i - 1] = 1;
            j = j - a[i - 1].weight;
        } else {
            x[i - 1] = 0;
        }
    }
    return V[n][C];
}

int main() {
    // setlocale(LC_ALL, "en_US.UTF-8");
    // freopen(NULL, "w", stdout);
    cout << "请输入物品数量：";
    cin >> n;
    cout << "请输入背包容量：";
    cin >> C;
    for (int i = 0; i < n; i++) {
        cout << "物品" << i + 1 << "的重量w[" << i + 1 << "]及其价值v[" << i + 1 << "]：";
        cin >> goods[i].weight;
        cin >> goods[i].value;
    }
    int sum2 = KnapSack(n, goods, C, X);
    cout << "动态规划法求解0/1背包问题:\n[";
    for (int i = 0; i < n; i++)
        cout << X[i] << " ";  // 输出所求X[n]矩阵
    cout << "]   装入总价值" << sum2 << endl;
    system("pause");
    return 0;
}