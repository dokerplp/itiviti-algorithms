#include <iostream>
#include <vector>

using namespace std;

bool is_possible(vector<int> arr, int val, int k) {
    vector<int> vec;
    vec.push_back(arr.front());
    int counter = 1;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] - vec.back() >= val) {
            vec.push_back(arr[i]);
            counter++;
            if (counter == k) return true;
        }
    }
    return false;
}

int bin_search(vector<int> arr, int k) {
    int l = 0;
    int r = (arr.back() - arr.front()) / (k - 1) + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (is_possible(arr, m, k)) l = m;
        else r = m;
    }
    return l;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        arr.push_back(t);
    }
    cout << bin_search(arr, k);
    return 0;
}