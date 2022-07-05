#include <iostream>
#include <map>
#include <vector>

using namespace std;

map<int, int> vertex;
vector<pair<int, int>> edges;
map<int, int> transit;
map<int, string> transit_way;
vector<string> ans;

void set_transit() {
    transit[0] = 6;
    transit_way[0] = "EF+\nAE-\nFG-";
    transit[1] = 7;
    transit_way[1] = "FG+\nBF-\nGH-";
    transit[2] = 4;
    transit_way[2] = "FG+\nCG-\nEF-";
    transit[3] = 5;
    transit_way[3] = "EH+\nDH-\nEF-";

    transit[6] = 0;
    transit_way[6] = "EF+\nAE-\nFG-";
    transit[7] = 1;
    transit_way[1] = "FG+\nBF-\nGH-";
    transit[4] = 2;
    transit_way[2] = "FG+\nCG-\nEF-";
    transit[5] = 3;
    transit_way[3] = "EH+\nDH-\nEF-";
}

void set_edges() {
    edges.emplace_back(0, 1);
    edges.emplace_back(1, 2);
    edges.emplace_back(2, 3);
    edges.emplace_back(3, 0);

    edges.emplace_back(4, 5);
    edges.emplace_back(5, 6);
    edges.emplace_back(6, 7);
    edges.emplace_back(7, 4);

    edges.emplace_back(0, 4);
    edges.emplace_back(1, 5);
    edges.emplace_back(2, 6);
    edges.emplace_back(3, 7);
}

char char_from_num(int num) {
    return char("A"[0] + num);
}

void adjacent_vertex(int v1, int v2) {
    while (vertex[v1] > 0 && vertex[v2] > 0) {
        vertex[v1]--;
        vertex[v2]--;
        string a;
        a += char_from_num(v1);
        a += char_from_num(v2);
        a += "-";
        ans.push_back(a);
    }
}

void opposite_vertex(int v1, int v2) {
    while (vertex[v1] > 0 && vertex[v2] > 0) {
        vertex[v1]--;
        vertex[v2]--;
        string a;
        a += transit_way[v1];
        ans.push_back(a);
    }
}

int main() {

    set_transit();
    set_edges();

    int control = 0;
    int group1_control = 0;
    for (int i = 0; i < 8; i++) {
        int k;
        cin >> k;
        vertex[i] = k;
        control += k;
        if (i == 0 || i == 2 || i == 5 || i == 7) group1_control++;
    }

    if (control % 2 == 1 || group1_control % 2 == 1) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    for (auto edge: edges) {
        adjacent_vertex(edge.first, edge.second);
    }

    for (auto trans: transit) {
        opposite_vertex(trans.first, trans.second);
    }

    for (auto v: vertex) {
        if (v.second != 0) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    for (const auto& a: ans) {
        cout << a << endl;
    }

    return 0;
}