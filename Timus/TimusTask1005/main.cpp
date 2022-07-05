#include <iostream>
#include <cmath>

using namespace std;

int find_max(int a, int b) {
    if (a > b) return a;
    return b;
}

int main() {

    int n;
    cin >> n;

    int sum = 0;
    int arr[n + 1];
    arr[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> arr[i];
        sum += arr[i];
    }


    int mid = ceil((double) sum / 2);

    int d1[mid + 1];
    int d2[mid + 1];

    for (int i = 0; i < mid + 1; i++) {
        d1[i] = 0;
    }
    d2[0] = 0;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < mid + 1; j++) {
            d2[j] = d1[j];
            if (arr[i] <= j) {
                d2[j] = find_max(d2[j], d1[j - arr[i]] + arr[i]);
            }
        }
        for (int k = 0; k < mid + 1; k++) {
            d1[k] = d2[k];
            d2[k] = 0;
        }
    }

    cout << abs(sum - 2 * d1[mid]);

    return 0;
}
