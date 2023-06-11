/*
 * Q24894 - Convex hull trick
 * Date: 2023.6.12
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<i64, i64>;

struct line {
    i64 y0, m;
    line(i64 y0, i64 m): y0(y0), m(m) {}
};

inline double cx(const line& a, const line& b) {
    return (double)(a.y0 - b.y0) / (b.m - a.m);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    vector<ii> v(N);
    for (auto& [x, y] : v) cin >> x >> y;
    sort(v.begin(), v.end());

    deque<line> hl; hl.emplace_back(v[0].second, v[0].first);
    int sz = 1;
    i64 ans = 0;
    for (int i = 1; i < N; ++i) {
        const auto& [x, y] = v[i];

        int l = 0, r = sz-1;
        while (l < r) {
            int mid = (l + r)>>1;
            if (x <= y * cx(hl[mid], hl[mid+1])) r = mid;
            else l = mid+1;
        }
        ans = max(ans, hl[l].m * x + hl[l].y0 * y);

        line ln(y, x);
        if (sz > 0 && hl[sz-1].m == ln.m)
            sz--, hl.pop_back();
        while (sz > 1 && cx(hl[sz-1], ln) <= cx(hl[sz-2], hl[sz-1]))
            sz--, hl.pop_back();
        sz++, hl.emplace_back(ln);
    }

    cout << ans;
    return 0;
}
