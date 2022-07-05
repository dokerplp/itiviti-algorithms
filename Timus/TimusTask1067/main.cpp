#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

unordered_map<string, set<string>> dirs;

vector<string> split(const string& s, char delimiter)
{
    vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

void spacer(int n) {
    for (int i = 0; i < n; i++) cout << " ";
}

void print_tree(string dir, int depth) {

    auto cmp = [](string a, string b){return a > b;};
    priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);
    for (string d: dirs[dir]) pq.push(d);

    while (!pq.empty()) {
        string d = pq.top();
        pq.pop();
        spacer(depth);
        cout << d << endl;
        if (dirs.find(dir + '\\' + d) != dirs.end()) {
            print_tree(dir + '\\' + d, depth + 1);
        }
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string parent;
        string s;
        cin >> s;
        for (string & d: split(s, '\\')) {
            dirs[parent].insert(d);
            parent += '\\' + d;
        }
    }

    string parent;
    print_tree(parent, 0);

}