#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

#define INF INT32_MAX

struct vertex {
    int dist;
    bool visited;
    int parent;
};

struct edge {
    int name;
    int delay;

    bool operator==(const edge &e) const {
        return name == e.name;
    }
};

class MyHashFunction {
public:
    size_t operator()(const edge &e) const {
        return hash<int>()(e.name);
    }
};

vector<int> delay;
unordered_set<string> telegraphs;
unordered_map<int, vertex> vertexes;
unordered_map<string, int> name_to_index;
unordered_map<int, string> index_to_name;

auto cmp = [](const int b, const int a) {
    if (a == b) return false;
    if (vertexes[a].dist == vertexes[b].dist) return a > b;
    return vertexes[a].dist < vertexes[b].dist;
};
priority_queue<int, vector<int>, decltype(cmp)> graph(cmp);

bool does_telegraph_exist(string &t) {
    return telegraphs.count(t) != 0;
}

unordered_set<edge, MyHashFunction> find_edges(int k) {
    string t = index_to_name[k];
    unordered_set<edge, MyHashFunction> edges;

    for (int i = 0; i < 10; i++) {
        for (char c = '0'; c <= '9'; c++) {
            string t_copy = t;
            t_copy[i] = c;
            if (does_telegraph_exist(t_copy)) {
                int tn = name_to_index[t_copy];
                if (tn != k) edges.insert({tn, delay[i]});
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            string t_copy = t;
            char a = t_copy[i];
            char b = t_copy[j];
            t_copy[i] = b;
            t_copy[j] = a;
            if (does_telegraph_exist(t_copy)) {
                int tn = name_to_index[t_copy];
                if (tn != k) edges.insert({tn, delay[i]});
            }
        }
    }

    return edges;
}

int main() {
    int n;
    cin >> n;

    telegraphs.reserve(n);
    vertexes.reserve(n);
    index_to_name.reserve(n);
    name_to_index.reserve(n);

    for (int i = 0; i < 10; i++) {
        int d;
        cin >> d;
        delay.push_back(d);
    }

    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        telegraphs.insert(t);
        vertexes[i + 1] = {INF, false, -1};
        index_to_name[i + 1] = t;
        name_to_index[t] = i + 1;
    }

    int cur = 1;
    vertexes[cur].dist = 0;
    graph.push(1);
    while (!(cur == n || graph.empty())) {
        for (const edge &e: find_edges(cur)) {
            if (!vertexes[e.name].visited && vertexes[cur].dist + e.delay < vertexes[e.name].dist) {
                vertexes[e.name].dist = vertexes[cur].dist + e.delay;
                graph.push(e.name);
                vertexes[e.name].parent = cur;
            }
        }
        vertexes[cur].visited = true;
        graph.pop();
        cur = graph.top();
    }

    if (vertexes[n].dist >= INF) cout << -1;
    else {
        cout << vertexes[n].dist << endl;
        int parent = n;
        int slaves = 1;
        stack<int> ans;
        while (parent != 1) {
            ans.push(parent);
            parent = vertexes[parent].parent;
            slaves++;
        }
        cout << slaves << endl;
        cout << "1 ";
        while (!ans.empty()) {
            cout << ans.top() << " ";
            ans.pop();
        }
    }

    return 0;
}