#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

#define INF INT32_MAX

enum type {
    FIELD = 1,
    FOREST = 2,
    WATER = INF
};

struct vertex {
    int32_t x, y;
};

vector<vector<double>> dist;
vector<vector<bool>> visited;
vector<vector<type>> types;
vector<vector<pair<vertex, char>>> parents;

auto cmp = [](const vertex & a, const vertex & b){
    if (a.x == b.x && a.y == b.y) return false;
    if (dist[a.y][a.x] == dist[b.y][b.x]) return a.y * 10000 + a.x > b.y * 10000 + b.x;
    return dist[a.y][a.x] < dist[b.y][b.x];
};
set<vertex, decltype(cmp)> graph(cmp);

type getType(char c) {
    switch (c) {
        case '.':
            return FIELD;
        case 'W':
            return FOREST;
        default:
            return WATER;
    }
}

int main() {

    int32_t n, m, y1, x1, y2, x2;
    cin >> n >> m >> y1 >> x1 >> y2 >> x2;
    x1--;
    y1--;
    x2--;
    y2--;

    dist.resize(n);
    for (int i = 0; i < n; i++) dist[i].resize(m, INF);

    visited.resize(n);
    for (int i = 0; i < n; i++) visited[i].resize(m, false);

    parents.resize(n);
    for (int i = 0; i < n; i++) parents[i].resize(m, pair(vertex({-1, -1}), '\0'));

    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        vector<type> v;
        for (char c : line) v.push_back(getType(c));
        types.push_back(v);
    }

    vertex cur = {x1, y1};
    visited[cur.y][cur.x] = true;
    dist[cur.y][cur.x] = 0;
    graph.insert(cur);
    while (!(cur.x == x2 && cur.y == y2)) {
        int32_t x = cur.x;
        int32_t y = cur.y;

        if (x > 0 && !visited[y][x - 1]) {
            vertex v = {x - 1, y};
            if (dist[y][x] + types[y][x - 1] < dist[y][x - 1]) {
                dist[y][x - 1] = dist[y][x] + types[y][x - 1];
                parents[y][x - 1] = pair(cur, 'W');
            }
            graph.insert(v);
        }

        if (x < m - 1 && !visited[y][x + 1]) {
            vertex v = {x + 1, y};
            if (dist[y][x] + types[y][x + 1] < dist[y][x + 1]) {
                dist[y][x + 1] = dist[y][x] + types[y][x + 1];
                parents[y][x + 1] = pair(cur, 'E');
            }
            graph.insert(v);
        }

        if (y > 0 && !visited[y - 1][x]) {
            vertex v = {x, y - 1};
            if (dist[y][x] + types[y - 1][x] < dist[y - 1][x]) {
                dist[y - 1][x] = dist[y][x] + types[y - 1][x];
                parents[y - 1][x] = pair(cur, 'N');
            }
            graph.insert(v);
        }

        if (y < n - 1 && !visited[y + 1][x]) {
            vertex v = {x, y + 1};
            if (dist[y][x] + types[y + 1][x] <= dist[y + 1][x]) {
                dist[y + 1][x] = dist[y][x] + types[y + 1][x];
                parents[y + 1][x] = pair(cur, 'S');
            }
            graph.insert(v);
        }

        visited[y][x] = true;
        graph.erase(cur);
        cur = *graph.begin();
    }

    if (dist[y2][x2] >= INF) {
        cout << -1;
    } else {
        cout << dist[y2][x2] << endl;
        string ans;
        while (!(cur.x == x1 && cur.y == y1)) {
            auto p = parents[cur.y][cur.x];
            cur = p.first;
            ans = p.second + ans;
        }
        cout << ans;
    }
}