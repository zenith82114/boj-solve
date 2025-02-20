/*
 * Q17411 - O(n log n) LIS
 * Date: 2025.2.20
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1e6 + 4, MOD = 1e9 + 7, INF = 1e9 + 1;

int a[MAXN];
vector<pair<int, int> > v[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    v[0].emplace_back(INF, 0);
    v[0].emplace_back(-INF, 1);
    int m = 0;
    int n; cin >> n;
    while (n--) {
        int x; cin >> x;
        int p = lower_bound(a, a + m, x) - a;
        if (p == m) v[++m].emplace_back(INF, 0);
        a[p] = x;
        auto lb = lower_bound(v[p].rbegin(), v[p].rend(), make_pair(x, 0));
        int cnt = (v[p].back().second - lb->second + MOD) % MOD;
        v[p + 1].emplace_back(x, (v[p + 1].back().second + cnt) % MOD);
    }

    cout << m << ' ' << v[m].back().second;
    return 0;
}
