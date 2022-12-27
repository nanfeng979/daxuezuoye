#include <iostream>
#include <algorithm>

using namespace std;

struct Skill {
    string name; // 技能名称
    int cost; // 消耗天赋值
    int attack; // 获得的攻击力
    int defense; // 获得的防御力
};

bool cmp(Skill a, Skill b) {
    return a.defense > b.defense; // 按防御力从大到小排序
}

int getMaxDefense(Skill *skills, int left, int right, int talent) {
    if (left == right) { // 如果只有一个技能
        if (talent >= skills[left].cost) { // 如果角色的天赋值足够学习当前技能
            return skills[left].defense; // 则返回该技能的防御力
        } else {
            return 0; // 否则返回0
        }
    }
    int mid = left + (right - left) / 2; // 取中间值
    int maxDefense = 0; // 角色的最大防御力
    for (int i = left; i <= right; i++) { // 枚举每一组技能的学习情况
        int defense = 0; // 角色的防御力
        int cost = 0; // 消耗的天赋值
        for (int j = left; j <= i; j++) { // 枚举当前组的技能
            if (cost + skills[j].cost > talent) { // 如果当前的天赋值已经不够学习当前技能了
                break; // 则跳出循环
            }
            cost += skills[j].cost; // 增加天赋值
            defense += skills[j].defense; // 增加防御力
        }
        maxDefense = max(maxDefense, defense + getMaxDefense(skills, i + 1, right, talent - cost)); // 取当前组技能学习和不学习两种情况的最大值
    }
    return maxDefense; // 返回角色的最大防御力
}

int main() {
    int talent = 200; // 角色天赋值
    Skill skills[9] = {
            {"技能1", 10, 10, 10},
            {"技能2", 20, 50, 20},
            {"技能3", 30, 40, 80},
            {"技能4", 40, 60, 20},
            {"技能5", 50, 40, 80},
            {"技能6", 15, 50, 20},
            {"技能7", 55, 70, 20},
            {"技能8", 70, 100, 30},
            {"技能9", 80, 110, 100}
    }; // 技能信息
    sort(skills, skills + 9, cmp); // 将技能按防御力从大到小排序
    int totalDefense = getMaxDefense(skills, 0, 8, talent); // 角色最大防御力

    cout << "角色的最大防御力为：" << totalDefense << endl;
    return 0;
}