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

int getMaxDefense(Skill *skills, int n, int talent) {
    int totalDefense = 0;

    for (int i = 0; i < 9; i++) {
        if (talent >= skills[i].cost) { // 如果角色的天赋值足够学习当前技能
            talent -= skills[i].cost; // 扣除天赋值
            totalDefense += skills[i].defense; // 增加防御力
        }
    }

    return totalDefense; // 返回角色的最大防御力
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

    int totalDefense = getMaxDefense(skills, 9, talent); // 角色最大防御力
    
    cout << "本次使用贪心算法：" << endl;
    cout << "角色的最大防御力为：" << totalDefense << endl;

    return 0;
}