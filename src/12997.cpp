/*
 * Q12997 - Convex hull
 * Date: 2024.1.16
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    using i64 = int64_t;

    int n; cin >> n;
    vector<pair<i64, i64> > v(n);
    for (auto& [v1, v2] : v) cin >> v1 >> v2;

    vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
        [&v] (int i, int j) { return v[i] > v[j]; }
    );

    auto ccw = [&v] (int a, int b, int c) {
        const auto& [a1, a2] = v[a];
        const auto& [b1, b2] = v[b];
        const auto& [c1, c2] = v[c];
        i64 r = b2*c1*(a1 - b1)*(a2 - c2) - b1*c2*(a2 - b2)*(a1 - c1);
        return r? r < 0? -1 : 1 : 0;
    };

    vector<int> hl; int sz = 0;
    for (int i : idx) {
        while (sz > 1 && ccw(hl[sz-2], hl[sz-1], i) <= 0) {
            hl.pop_back(); --sz;
        }
        hl.emplace_back(i); ++sz;
    }
    while (sz > 1 && v[hl[sz-2]].second >= v[hl[sz-1]].second) {
        hl.pop_back(); --sz;
    }

    for (int i = 0; i < n; ++i) {
        auto p = lower_bound(hl.begin(), hl.end(), i,
            [&v] (int a, int b) { return v[a] > v[b]; }
        );
        if (p == hl.end()) continue;
        if (v[*p] == v[i]) cout << (i+1) << ' ';
        else if (p != hl.begin() && ccw(*prev(p), i, *p) == 0) cout << (i+1) << ' ';
    }
    return 0;
}
