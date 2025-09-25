/*
 * Q2261 - geometry, DnC
 * Date: 2025.9.25
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Vec2 { int x, y; } pt[100000];
int y_ord[100000];

int sqr_dist(int i, int j) {
    int dx = pt[i].x - pt[j].x, dy = pt[i].y - pt[j].y;
    return dx*dx + dy*dy;
}

int dnc(int s, int e) {
    int ans = INT32_MAX;
    if (e - s <= 3) {
        for (int i = s; i < e; ++i)
        for (int j = i + 1; j < e; ++j) ans = min(ans, sqr_dist(i, j));
        return ans;
    }

    const int mid = (s + e) / 2;
    vector<int> temp(y_ord + s, y_ord + e);
    for (int i = s, j = mid, k = 0; k < e - s; ++k) {
        y_ord[(temp[k] < mid? i : j)++] = temp[k];
    }
    ans = min(dnc(s, mid), dnc(mid, e));
    const int delta = (int)ceil(sqrt(ans));

    vector<int> temp2;
    for (int i : temp) {
        if (pt[mid].x - delta <= pt[i].x && pt[i].x <= pt[mid].x + delta) {
            temp2.emplace_back(i);
        }
    }
    const int t = temp2.size();
    for (int ii = 0; ii < t; ++ii) {
        int i = temp2[ii];
        for (int jj = ii + 1; jj < t; ++jj) {
            int j = temp2[jj];
            if (pt[i].y + delta <= pt[j].y) break;
            ans = min(ans, sqr_dist(i, j));
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> pt[i].x >> pt[i].y;
    sort(pt, pt + n, [] (const Vec2& a, const Vec2& b) { return a.x < b.x; });
    iota(y_ord, y_ord + n, 0);
    sort(y_ord, y_ord + n, [] (int i, int j) { return pt[i].y < pt[j].y; });

    cout << dnc(0, n);
    return 0;
}
