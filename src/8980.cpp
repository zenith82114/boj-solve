/*
 * Q8980 - Greedy
 * Date: 2024.5.22
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, c; cin >> n >> c;
    int m; cin >> m;
    struct task { int st, fi, qt; };
    vector<task> v(m);
    for (auto& [st, fi, qt] : v) cin >> st >> fi >> qt;
    sort(v.begin(), v.end(), [] (const task& a, const task& b) {
        return a.fi < b.fi;
    });

    map<int, int> mp;
    mp[0] = c;
    int ans = 0;
    for (auto [st, fi, qt] : v) {
        while (qt) {
            auto ub = mp.upper_bound(st);
            if (ub == mp.begin()) break;
            auto [thr_fi, thr_qt] = *(--ub);
            int delta = min(thr_qt, qt);
            if (delta == thr_qt) mp.erase(thr_fi);
            else mp[thr_fi] -= delta;
            mp[fi] += delta;
            qt -= delta;
            ans += delta;
        }
    }

    cout << ans;
    return 0;
}
