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

    // 使用贪心算法，每次选择防御力最大的技能
    int totalDefence = 0;
    for (const auto& skill : skills) {
        // 如果当前技能的天赋消耗大于剩余天赋值，则退出循环
        if (skill.cost > talent) {
            break;
        }
        // 增加防御力，减少天赋值
        totalDefence += skill.defence;
        talent -= skill.cost;
    }

    cout << "Total defence: " << totalDefence << endl;

    return 0;
}