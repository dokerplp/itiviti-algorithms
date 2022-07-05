#include <iostream>
#include <queue>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    priority_queue<int> queue;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        queue.push(t);
    }

    int sum = 0;

    for (int i = 1; i < n + 1; i++) {
        if (i % k != 0) {
            sum += queue.top();
        }
        queue.pop();
    }

    cout << sum;

    return 0;
}
