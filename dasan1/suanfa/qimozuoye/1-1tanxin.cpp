#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 9;

// 技能信息
struct Skill {
    string name;  // 技能名称
    int cost;     // 消耗天赋值
    int attack;   // 获得的攻击力
    int defense;  // 获得的防御力
    Skill(string name, int cost, int attack, int defense) : name(name), cost(cost), attack(attack), defense(defense) {}
};

// 比较函数，按照攻击力和防御力的总和从大到小排序
bool cmp(Skill a, Skill b) {
    return a.attack + a.defense > b.attack + b.defense;
}

int main() {
    // 初始化技能信息
    vector<Skill> skills = {
        Skill("技能1", 10, 10, 10),
        Skill("技能2", 20, 50, 20),
        Skill("技能3", 30, 40, 80),
        Skill("技能4", 40, 60, 20),
        Skill("技能5", 50, 40, 80),
        Skill("技能6", 15, 50, 20),
        Skill("技能7", 55, 70, 20),
        Skill("技能8", 70, 100, 30),
        Skill("技能9", 80, 110, 100)
    };

    // 按照攻击力和防御力的总和从大到小排序
    sort(skills.begin(), skills.end(), cmp);

    int talent = 200;  // 初始天赋值
    int attack = 0;    // 初始攻击力
    int defense = 0;   // 初始防御力

    // 选择技能
    for(auto skill : skills) {
    // 如果技能的天赋值消耗大于当前剩余的天赋值，则跳过
    if (skill.cost > talent) continue;
        // 否则，学习该技能
        talent -= skill.cost;
        attack += skill.attack;
        defense += skill.defense;
    }


    cout << "攻击力: " << attack << endl;
    cout << "防御力: " << defense << endl;

return 0;
}