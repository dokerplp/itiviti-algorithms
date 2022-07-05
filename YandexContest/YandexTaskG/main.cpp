#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

map<char, int> weights;
map<char, int> letters;

int value(char c) {
    if (letters[c] < 2) return 0;
    return weights[c];
}

int main() {

    string s;
    cin >> s;

    for (char i = 'a'; i <= 'z'; i++) {
        int w;
        cin >> w;
        weights[i] = w;
        letters[i] = 0;
    }

    for (char c: s) letters[c]++;

    auto comparator = [](char a, char b){
        return value(a) < value(b);
    };
    priority_queue<char, vector<char>, decltype(comparator)> queue(comparator);

    for (auto el: letters) if (letters[el.first]) queue.push(el.first);

    string prefix;
    string middle;
    string postfix;
    while (!queue.empty()) {
        char c = queue.top();
        queue.pop();
        if (letters[c] > 1) {
            prefix += c;
            postfix = c + postfix;
            letters[c] -= 2;
        }
        while (letters[c]) {
            middle += c;
            letters[c]--;
        }
    }

    cout << prefix << middle << postfix;

    return 0;
}
