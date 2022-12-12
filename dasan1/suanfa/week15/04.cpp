#include <iostream>
#include <algorithm>

using namespace std;

int count = 0;

void print_permutation(int n, int *List, int cur) {
    if (cur == n) {
        for (int i = 0; i < n; i++) {
            cout << List[i] << " ";
        }
        cout << endl;
        ::count++;
        return;
    }

    for (int i = 1; i <= n; i++) {
        bool ok = true;
        for (int j = 0; j < cur; j++) {
            if (List[j] == i) {
                ok = false;
                break;
            }
        }
        if (ok) {
            List[cur] = i;
            print_permutation(n, List, cur + 1);
        }
    }
}

int main() {
    int n = 3;
    int *List = new int[n];
    print_permutation(n, List, 0);
    delete[] List;
    cout << ::count << endl;
    return 0;
}