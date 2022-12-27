#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

// 技能信息
struct Skill {
string name; // 技能名称
int cost; // 消耗天赋值
int attack; // 获得的攻击力
int defense; // 获得的防御力
Skill(string name, int cost, int attack, int defense) : name(name), cost(cost), attack(attack), defense(defense) {}
};

// 当前的攻击力和防御力
int attack, defense;

// 回溯函数
void dfs(int talent, vector<Skill>& skills, int index) {
// 如果所有技能都已经选择过，则更新答案
if (index == skills.size()) {
attack = max(attack, talent);
defense = max(defense, talent);
return;
}


// 不选择当前技能
dfs(talent, skills, index + 1);

// 如果当前天赋值足够，则选择当前技能
if (talent >= skills[index].cost) {
    dfs(talent - skills[index].cost, skills, index + 1);
}
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


// 进行回溯
dfs(200, skills, 0);

cout << "攻击力: " << attack << endl;
cout << "防御力: " << defense << endl;

return 0;
}