#include <iostream>
#include <algorithm>
using namespace std;

// 定义作业数量
const int n = 7;
// 定义机器数量
const int m = 3;

// 定义作业处理时间
int t[n] = {2, 14, 4, 16, 6, 5, 3};

// 贪心算法求解多机调度问题
void greedy() {
    // 对作业的处理时间进行排序
    sort(t, t + n);
    // 定义机器的处理时间
    int machine[m] = {0};
    // 遍历每个作业
    for (int i = 0; i < n; i++) {
        // 寻找处理时间最小的机器
        int min_machine = 0;
        for (int j = 1; j < m; j++) {
            if (machine[j] < machine[min_machine]) {
                min_machine = j;
            }
        }
        // 将作业分配给该机器进行处理
        machine[min_machine] += t[i];
    }
    // 输出机器的处理时间
    for (int i = 0; i < m; i++) {
        cout << "机器M" << i + 1 << "的处理时间为：" << machine[i] << endl;
    }
}

int main() {
    // 调用贪心算法求解多机调度问题
    greedy();
    return 0;
}