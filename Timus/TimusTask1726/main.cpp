#include <iostream>
#include <queue>
#include <cinttypes>

using namespace std;

int main() {
    int64_t n;
    cin >> n;

    priority_queue<int32_t> x_queue;
    priority_queue<int32_t> y_queue;

    int64_t x_sum = 0;
    int64_t y_sum = 0;
    for (int i = 0; i < n; i++) {
        int32_t  x, y;
        cin >> x >> y;
        x_queue.push(x);
        x_sum += x;
        y_queue.push(y);
        y_sum += y;
    }

    int64_t ans = 0;
    while (!x_queue.empty()) {
        int32_t cur_x = x_queue.top();
        x_queue.pop();
        x_sum -= cur_x;
        ans += cur_x * x_queue.size() - x_sum;
    }
    while (!y_queue.empty()) {
        int32_t cur_y = y_queue.top();
        y_queue.pop();
        y_sum -= cur_y;
        ans += cur_y * y_queue.size() - y_sum;
    }

    cout << (ans * 2) / (n * (n - 1));

    return 0;
}
