#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct element {
    int min, value;
};

int main() {
    int n, k;

    cin >> n >> k;

    stack<element> left, right;

    vector<int> ans;

    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;

        if (left.empty()) left.push({e, e});
        else left.push({min(left.top().min, e), e});

        if (left.size() == k) {
            if (!right.empty()) right.pop();
            while (!left.empty()) {
                element el = left.top();
                left.pop();
                if (right.empty()) right.push({el.value, el.value});
                else right.push({min(right.top().min, el.value), el.value});
            }
            ans.push_back(right.top().min);
        } else if (!right.empty()) {
            right.pop();
            ans.push_back(min(left.top().min, right.top().min));
        }
    }

    for (int e: ans) cout << e << " ";

    return 0;
}
