/*
 * Q1470 - DP
 * Date: 2024.3.14
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    struct item { int g, s, b, id; };

    int n, m; cin >> n >> m;
    vector<item> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].g >> v[i].s >> v[i].b;
        v[i].id = i;
    }
    v[0].g += m;
    sort(v.begin(), v.end(), [](const item& x, const item& y) {
        if (x.g != y.g) return x.g > y.g;
        if (x.s != y.s) return x.s > y.s;
        if (x.b != y.b) return x.b > y.b;
        return x.id < y.id;
    });

    int idx = 0;
    while (v[idx].id != 0) ++idx;
    auto [g0, s0, b0, id0] = v[idx];
    ++idx;

    vector<int> dp0(m+1), dp1(m+1, 0);

    for (; idx < n; ++idx) {
        auto [gi, si, bi, idi] = v[idx];
        if (gi < g0) break;

        dp0.swap(dp1);
        fill(dp1.begin(), dp1.end(), INT32_MAX>>1);

        int ds = s0 - si;
        int db = max(0, b0+1 - bi);
        if (ds+1 <= m) {
            for (int s = 0; s+ds < m; ++s) {
                dp1[s+ds+1] = min(dp1[s+ds+1], dp0[s]);
            }
        }
        if (ds+db <= m) {
            for (int s = 0; s+ds <= m; ++s) {
                dp1[s+ds] = min(dp1[s+ds], dp0[s] + db);
            }
        }

        if (all_of(dp1.begin(), dp1.end(),
            [m](int x) { return x > m; })) break;
    }

    cout << idx;
    return 0;
}
