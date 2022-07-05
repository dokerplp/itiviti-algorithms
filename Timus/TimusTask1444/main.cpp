#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct point {
    int index;
    int x;
    int y;
    double angle;
    double dist;
};

double angle(point a, point b) {
    double an = atan2(b.y - a.y, b.x - a.x) * 180 / M_PI;
    an = an > 0 ? an : an + 360;
    return an != 360 ? an : 0;
}

double dist(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int comparator(point a, point b) {
    return a.angle != b.angle ? a.angle < b.angle : a.dist < b.dist;
}

int main() {
    int n;
    cin >> n;

    vector<point> points;

    int x, y;
    cin >> x >> y;
    point start = {0, x, y, -1, -1};
    points.push_back(start);

    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        point p = {i, x, y};
        p.angle = angle(start, p);
        p.dist = dist(start, p);
        points.push_back(p);
    }

    sort(points.begin(), points.end(), comparator);

    int s = 0;
    for (int i = 1; i < n - 1; i++) {
        point p1 = points[i], p2 = points[i + 1];
        if (p2.angle - p1.angle >= 180) {
            s = i;
            break;
        }
    }

    cout << n << endl;
    cout << 1 << endl;
    for (int i = s + 1; i < n; i++) {
        cout << points[i].index + 1 << endl;
    }
    for (int i = 1; i < s + 1; i++) {
        cout << points[i].index + 1 << endl;
    }
}