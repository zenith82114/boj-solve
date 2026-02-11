/*
 * Q16216 - tree compression, DP
 * Date: 2026.2.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
const int MAXN = 3e5 + 4;
const i64 INF = INT64_MAX/3;

vector<ii> g[MAXN];
bitset<MAXN> need;
int cnt[MAXN];
vector<i64> dp1[MAXN], dp2[MAXN];

ii compress(int px, int x) {
    vector<ii> v;
    for (auto [y, _] : g[x]) if (y != px) {
        auto e = compress(x, y);
        if (e.first) v.push_back(e);
    }
    if (need[x] || x == 1 || v.size() >= 2) {
        g[x].swap(v);
        return make_pair(x, 1);
    }
    if (v.size() == 1) {
        v[0].second++;
        return v[0];
    }
    return make_pair(0, 0);
}

inline void upd_min(i64& a, i64 b) { a = min(a, b); }

void solve(int x) {
    if (need[x]) {
        cnt[x] = 1;
        dp1[x] = { INF, 0 };
        dp2[x] = { INF, 0 };
    }
    else {
        dp1[x] = { 0 };
        dp2[x] = { 0 };
    }

    for (auto [y, w] : g[x]) {
        solve(y);
        vector<i64> res1(dp1[x]), res2(dp2[x]);
        res1.resize(cnt[x] + cnt[y] + 1, INF);
        res2.resize(cnt[x] + cnt[y] + 1, INF);

        for (int i = cnt[x]; i >= 0; --i)
        for (int j = 1; j <= cnt[y]; ++j) {
            upd_min(res1[i + j], dp1[x][i] + dp1[y][j] + 2*w);
            upd_min(res2[i + j], min(
                dp1[x][i] + dp2[y][j] + w,
                dp1[y][j] + dp2[x][i] + 2*w
            ));
        }
        cnt[x] += cnt[y];

        dp1[y].clear();
        dp2[y].clear();
        dp1[x].swap(res1);
        dp2[x].swap(res2);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y, 1);
        g[y].emplace_back(x, 1);
    }
    for (int i = 0; i < k; ++i) {
        int x; cin >> x;
        need.set(x);
    }
    compress(0, 1);
    solve(1);
    for (int i = 1; i <= k; ++i) cout << dp2[1][i] << '\n';

    return 0;
}
