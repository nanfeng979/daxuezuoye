#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 9;
const int M = 201;

// 技能信息
struct Skill {
string name; // 技能名称
int cost; // 消耗天赋值
int attack; // 获得的攻击力
int defense; // 获得的防御力
Skill(string name, int cost, int attack, int defense) : name(name), cost(cost), attack(attack), defense(defense) {}
};

// 动态规划表
int dp[M][M];

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
};// 初始化动态规划表
for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
        dp[i][j] = -1;
    }
}
dp[0][0] = 0;  // 初始状态

// 进行动态规划
for (auto skill : skills) {
    for (int i = skill.cost; i < M; i++) {
        for (int j = skill.cost; j < M; j++) {
            // 如果之前的状态无效，则跳过
if (dp[i - skill.cost][j - skill.cost] == -1) continue;
// 更新状态
dp[i][j] = max(dp[i][j], dp[i - skill.cost][j - skill.cost] + skill.attack + skill.defense);
}
}
}

// 找到最优解
int attack = 0, defense = 0;
for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
        if (dp[i][j] > attack + defense && i + j <= 200) {
            attack = i;
            defense = j;
        }
    }
}

cout << "攻击力: " << attack << endl;
cout << "防御力: " << defense << endl;

return 0;
}