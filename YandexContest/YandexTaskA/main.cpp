#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;

    int flowers = 0;
    int counter = 0;
    int ans = -1;
    int ans_right = -1;
    int cur = -1;

    for (int i = 0; i < n; i++) {
        int now;
        cin >> now;

        if (cur == now) counter++;
        else counter = 1;

        if (counter < 3) flowers++;
        else flowers = 2;

        cur = now;
        if (flowers > ans) {
            ans = flowers;
            ans_right = i + 1;
        }
    }

    cout << ans_right - ans + 1 << " " << ans_right;

    return 0;
}
