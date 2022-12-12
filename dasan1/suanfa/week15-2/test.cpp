#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 7;
const int W = 150;

int n = N;
int w = W;
int wt[N] = {35, 30, 60, 50, 40, 10, 25};
int val[N] = {10, 49, 30, 50, 35, 40, 30};

vector<string> items = {"A", "B", "C", "D", "E", "F", "G"};

int dp[N+1][W+1];

int knapsack() {
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= w; j++) {
            if (wt[i-1] <= j) {
                dp[i][j] = max(val[i-1] + dp[i-1][j-wt[i-1]], dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    int j = w;
    vector<string> selected;
    for (int i = n; i > 0 && j > 0; i--) {
        if (dp[i][j] != dp[i-1][j]) {
            selected.push_back(items[i-1]);
            j -= wt[i-1];
        }
    }

    cout << "Selected items: ";
    for (int i = selected.size()-1; i >= 0; i--) {
        cout << selected[i] << " ";
    }
    cout << endl;

    return dp[n][w];
}

void add_item(string name, int weight, int value) {
    if (weight > w) {
        cout << "Error: item is too heavy to be placed in the knapsack" << endl;
        return;
    }

    items.push_back(name);
    wt[n] = weight;
    val[n] = value;
    n++;
}

int main() {
    cout << "Total value: " << knapsack() << endl;

    string name;
    int weight, value;
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter item weight: ";
    cin >> weight;
    cout << "Enter item value: ";
    cin >> value;

    add_item(name, weight, value);
    cout << "Total value: " << knapsack() << endl;

    return 0;
}