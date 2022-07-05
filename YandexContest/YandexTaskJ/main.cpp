#include <iostream>
#include <list>

using namespace std;

int main() {

    int n;
    cin >> n;

    list<int> queue;
    auto mid = queue.begin();
    int capacity = 0;

    for (int i = 0; i < n; i++) {
        char com;
        cin >> com;

        int val = -1;
        if (com != '-') cin >> val;

        switch (com) {
            case '+':
                queue.push_back(val);
                if (capacity % 2 == 0) {
                    if (capacity == 0) mid = queue.begin();
                    else mid++;
                }
                capacity++;
                break;
            case '*':
                if (capacity == 0) queue.push_back(val);
                else {
                    auto prev = mid;
                    auto next = mid.operator++();
                    queue.insert(next, val);
                    mid = prev;
                }
                if (capacity % 2 == 0) {
                    if (capacity == 0) mid = queue.begin();
                    else mid++;
                }
                capacity++;
                break;
            case '-':
                int val = *queue.begin();
                cout << val << endl;
                if (capacity % 2 == 0) {
                    mid++;
                }
                queue.pop_front();
                capacity--;
                break;
        }
    }

    return 0;
}
