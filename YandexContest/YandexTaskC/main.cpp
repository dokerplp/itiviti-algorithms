#include <iostream>
#include <string>
#include <map>
#include <stack>

using namespace std;

map<string, int> elements;
stack<map<string, int>> history;

bool element_exists(const string& key) {
    return elements.find(key) != elements.end();
}

bool history_exists(const string& key) {
    return history.top().find(key) != history.top().end();
}

bool is_number(const string& str) {
    return isdigit(str[0]) || str[0] == "-"[0] && isdigit(str[1]);
}

void init(const string& key) {
    if (!element_exists(key)) {
        elements[key] = 0;
    }
}

void create_map() {
    map<string, int> hstr;
    history.push(hstr);
}

void destroy_map() {
    for (const auto& el: history.top()) {
        elements[el.first] = el.second;
    }
    history.pop();
}

int get_element(const string& key) {
    init(key);
    return elements[key];
}

int set_element(const string& key, int val) {
    init(key);
    if (!history_exists(key)) history.top()[key] = elements[key];
    elements[key] = val;
    return val;
}

void parse_line(const string& line) {
    string left;
    string right;
    bool flag = false;

    for (char c: line) {
        if (c == "="[0]) {
            flag = true;
            continue;
        }
        if (!flag) left += c;
        else right += c;
    }

    if (is_number(right)) {
        set_element(left, stoi(right));
    } else {
        cout << set_element(left, get_element(right)) << endl;
    }
}

int main() {

    string s;

    create_map();

    while (cin >> s) {
        if (s == "{") {
            create_map();
        }
        else if (s == "}") {
            destroy_map();
        }
        else parse_line(s);
    }

    return 0;
}

