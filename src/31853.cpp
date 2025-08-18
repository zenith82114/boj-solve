/*
 * Q31853 - sweeping
 * Date: 2025.8.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> c;
void enc(int& x) {
    x = lower_bound(begin(c), end(c), x) - begin(c);
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _, m; cin >> _ >> m;
    vector<pair<int, int> > v(m);
    for (auto& [x, y] : v) {
        cin >> x >> y;
        if (x > y) swap(x, y);
        c.emplace_back(x);
        c.emplace_back(y);
    }
    sort(begin(v), end(v));
    sort(begin(c), end(c));
    vector<int> y2x(2*m, 2*m);
    for (auto& [x, y] : v) {
        enc(x), enc(y);
        y2x[y] = x;
    }

    i64 ans = 0;
    for (int j = 0; j < m; ++j) {
        auto [xj, yj] = v[j];
        int cnt = 0;
        int yi = yj - 1;
        for (int k = m - 1; j < k; --k) {
            auto [xk, yk] = v[k];
            while (xk < yi) cnt += (y2x[yi--] < xj);
            if (yj < yk) ans += cnt;
        }
    }
    cout << ans;
    return 0;
}
