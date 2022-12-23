#include <iostream>
#include <vector>

using namespace std;

// 定义技能结构体，其中 attack 表示攻击力，defence 表示防御力，cost 表示天赋消耗
struct Skill {
    int attack;
    int defence;
    int cost;
};

int maxDefence = 0; // 全局变量，用于记录最大防御力

// 回溯函数，skills 表示技能数组，index 表示当前考虑的技能的编号，talent 表示剩余天赋值，defence 表示当前已获得的防御力
void backtrack(const vector<Skill>& skills, int index, int talent, int defence) {
    // 如果当前技能的编号已经大于技能数组的大小，则更新最大防御力并退出函数
    if (index > skills.size()) {
        maxDefence = max(maxDefence, defence);
        return;
    }

    // 如果当前技能的天赋消耗大于剩余天赋值，则退出函数
    if (skills[index].cost > talent) {
        return;
    }

    // 选择当前技能
    backtrack(skills, index + 1, talent - skills[index].cost, defence + skills[index].defence);
    // 不选择当前技能
    backtrack(skills, index + 1, talent, defence);
}

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

    // 调用回溯函数
    backtrack(skills, 0, talent, 0);

    cout << "Total defence: " << maxDefence << endl;

    return 0;
}