#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义技能结构体，其中 attack 表示攻击力，defence 表示防御力，cost 表示天赋消耗
struct Skill {
    int attack;
    int defence;
    int cost;
};

int main() {
    // 读入天赋值
    int talent;
    cin >> talent;

    // 读入技能数组
    vector<Skill> skills;
    int attack, defence, cost;
    while (cin >> attack >> defence >> cost) {
        skills.push_back({attack, defence, cost});
    }

    // 使用贪心算法 + 动态规划的方法
    vector<int> dp(talent + 1, 0);
    for (int i = 0; i < skills.size(); i++) {
        for (int j = talent; j >= skills[i].cost; j--) {
            // 使用贪心算法选择当前技能
            if (skills[i].defence > dp[j - skills[i].cost]) {
                // 更新状态，在不超过总天赋的情况下，选择当前技能后的防御力最大值
                dp[j] = max(dp[j], dp[j - skills[i].cost] + skills[i].defence);
            }
        }
    }

    cout << "Total defence: " << dp[talent] << endl;

    return 0;
}