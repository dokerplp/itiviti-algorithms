#include <iostream>
#include <vector>

using namespace std;

vector<int> comp;

int parent(int i) {
    while (comp[i] != i) i = comp[i];
    return i;
}

void union_set(int i, int j) {
    int p1 = parent(i);
    int p2 = parent(j);
    comp[p1] = min(p1, p2);
    comp[p2] = min(p1, p2);
}

int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        comp.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        union_set(i, k - 1);
    }

    int u = 0;
    for (int i = 0; i < n; i++) {
        if (comp[i] == i) u++;
    }

    cout << u;

    return 0;
}
