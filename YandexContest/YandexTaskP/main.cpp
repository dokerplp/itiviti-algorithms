#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<vector<int>> weights;
vector<vector<bool>> g;
vector<bool> visited;

void make_g(int w) {
    g.clear();
    g.resize(weights.size());
    for (int i = 0; i < weights.size(); i++) {
        for (int j = 0; j < weights.size(); j++)
            g[i].push_back(weights[i][j] <= w);
    }
}

void from_one_to_all(int v, int& counter) {
    visited[v] = true;
    counter++;
    for (int i = 0; i < weights.size(); i++) {
        if (!visited[i] && g[v][i]) from_one_to_all(i, counter);
    }
}

void from_all_to_one(int v, int& counter) {
    visited[v] = true;
    counter++;
    for (int i = 0; i < weights.size(); i++) {
        if (!visited[i] && g[i][v]) from_all_to_one(i, counter);
    }
}

bool from_all_to_all(int w) {
    make_g(w);

    visited.clear();
    visited.resize(weights.size(), false);
    int counter_from = 0;
    from_one_to_all(0, counter_from);

    visited.clear();
    visited.resize(weights.size(), false);
    int counter_to = 0;
    from_all_to_one(0, counter_to);

    return counter_from == weights.size() && counter_to == weights.size();
}

int64_t execute_order_66() {
    int l = 0;
    int r = 2000000000;
    while (l < r) {
        int m = (l + r) / 2;
        if (from_all_to_all(m)) r = m;
        else l = m + 1;
    }
    return l;
}

int main() {

    int64_t n;
    cin >> n;

    weights.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c;
            cin >> c;
            weights[i].push_back(c);
        }
    }

    cout << execute_order_66();

    return 0;
}