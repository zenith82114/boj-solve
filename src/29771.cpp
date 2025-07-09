/*
 * Q29771 - tree compression
 * Date: 2025.7.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5;

vector<int> g[MAXN];
int rmq[20][2 * MAXN];
array<int, MAXN> dep, ts, te;
array<i64, MAXN> ps;
auto cmp = [] (const int& x, const int& y) { return ts[x] < ts[y]; };
vector<int> v;

void dfs(int px, int x, int& clk) {
    ts[x] = clk;
    rmq[0][clk++] = x;
    for (int y : g[x]) if (y != px) {
        dep[y] = dep[x] + 1;
        ps[y] = ps[x] + y;
        dfs(x, y, clk);
        rmq[0][clk++] = x;
    }
    te[x] = clk - 1;
}

int lca(int x, int y) {
    int l = ts[x], r = ts[y]; if (l > r) swap(l, r);
    int t = r - l + 1;
    int i = 19; while (~t & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return dep[x1] < dep[x2]? x1 : x2;
}

pair<int, i64> dp(int x, size_t& idx) {
    int cnt = 1;
    i64 sum = x;
    while (idx < v.size() && te[v[idx]] <= te[x]) {
        int y = v[idx++];
        auto [cnt_y, sum_y] = dp(y, idx);
        cnt += cnt_y + (dep[y] - dep[x] - 1);
        sum += sum_y + (ps[y] - ps[x] - y);
    }
    return { cnt, sum };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
    }
    ps[0] = 0;
    int clk = 0; dfs(-1, 0, clk);

    for (int i = 1; i < 20; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*n; ++j) {
        int x1 = rmq[i - 1][j], x2 = rmq[i - 1][j + (1<<i>>1)];
        rmq[i][j] = dep[x1] < dep[x2]? x1 : x2;
    }

    int q; cin >> q; while (q--) {
        int k; cin >> k;
        v.resize(k); for (int& x : v) cin >> x;
        sort(v.begin(), v.end(), cmp);
        for (int i = 0; i + 1 < k; ++i) v.emplace_back(lca(v[i], v[i + 1]));
        sort(v.begin(), v.end(), cmp);
        v.erase(unique(v.begin(), v.end()), v.end());

        size_t idx = 1;
        auto [cnt, sum] = dp(v[0], idx);
        cout << cnt << ' ' << sum << '\n';
    }

    return 0;
}
