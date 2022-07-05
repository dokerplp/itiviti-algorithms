#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, k;

    cin >> a >> b >> c >> d >> k;

    int cur = a;
    int prev;
    for (int i = 0; i < k; i++) {
        prev = cur;
        cur = cur * b - c;
        if (cur <= 0) {
            cout << 0;
            return 0;
        }
        if (cur >= d) cur = d;
        if (cur == prev) break;
    }

    cout << cur;
    return 0;
}

