#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<int>> v;
unordered_map<int, vector<int>> h;


int main() {
    int m, n, k;
    cin >> m >> n >> k;

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        h[x].push_back(y);
        v[y].push_back(x);
    }

    for (int i = 0; i < m; i++) {
        h[i + 1].push_back(0);
        h[i + 1].push_back(n + 1);
    }

    for (int i = 0; i < n; i++) {
        v[i + 1].push_back(0);
        v[i + 1].push_back(m + 1);
    }

    unordered_set<string> alone;

    int ans = 0;
    for (auto & d: h) {
        vector<int> line = d.second;
        sort(line.begin(), line.end());

        int a = line[0];
        for (int i = 1; i < line.size(); i++) {
            if (line[i] - a > 2) {
                ans++;
            } else if (line[i] - a == 2) {
                string key = to_string(d.first) + "-" + to_string(line[i] - 1);
                alone.insert(key);
            }
            a = line[i];
        }
    }

    for (auto & d: v) {
        vector<int> line = d.second;
        sort(line.begin(), line.end());

        int a = line[0];
        for (int i = 1; i < line.size(); i++) {
            if (line[i] - a > 2) {
                ans++;
            } else if (line[i] - a == 2) {
                string key = to_string(line[i] - 1) + "-" + to_string(d.first);
                if (alone.find(key) != alone.end()) ans++;
            }
            a = line[i];
        }
    }

    cout << ans;

    return 0;
}
