#include <iostream>
#include <vector>
#include <set>

using namespace std;

enum vertex_color {
    RED,
    BLUE,
    WHITE
};

vector<vector<int>> G;
set<int> not_visited;
vector<vertex_color> colors;

vertex_color anti_color(vertex_color color) {
    return (color == RED) ? BLUE : RED;
}

bool dfs(vertex_color color, int from, int to) {
    not_visited.erase(to);
    colors[to] = color;
    for (int v : G[to]) {
        if (colors[v] == color) return false;
        if (v != from && colors[v] == WHITE) {
            if (!dfs(anti_color(color), to, v)) return false;
        }
    }
    return true;
}

int main() {

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        colors.push_back(WHITE);
        not_visited.insert(i);
        G.emplace_back();
    }

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        while (a != 0) {
            G[a - 1].push_back(i);
            G[i].push_back(a - 1);
            cin >> a;
        }
    }

    bool ans = true;
    while (!not_visited.empty()) {
        if (!dfs(RED, -1, *not_visited.begin())) {
            ans = false;
            break;
        }
    }

    if (ans) {
        for (auto color : colors)
            cout << (color != RED);
    }
    else cout << -1;

    return 0;
}
