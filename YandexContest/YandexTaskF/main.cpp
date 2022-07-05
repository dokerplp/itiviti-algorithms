#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {

    ifstream file("/Users/twenty_one_thirteen/Desktop/ITMO/Курс2/Сем4/Алгосы/YandexContest/YandexTaskF/number.in");

    auto comparator = [](const string& s1, const string& s2) {
        return s1 + s2 < s2 + s1;
    };

    priority_queue<string, std::vector<string>, decltype(comparator)> queue(comparator);

    while (!file.eof()) {
        string s;
        file >> s;
        if (s.empty()) break;
        queue.push(s);
    }

    while (!queue.empty()) {
        cout << queue.top();
        queue.pop();
    }

    file.close();

    return 0;
}

