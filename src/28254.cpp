/*
 * Q28254 - Euler tour, HLD
 * Date: 2025.3.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<pair<int, int> > adj[500005];
vector<int> flags[500005];
array<int, 500005> sz, ts, ts_inv, te, tot, cnt;
i64 ans[500005];
i64 tmp = 0;

void prep(int px, int x, int& clk) {
    sz[x] = flags[x].size();
    ts[x] = clk;
    ts_inv[clk] = x;
    ++clk;
    for (const auto& [y, _] : adj[x]) if (y != px) {
        prep(x, y, clk);
        sz[x] += sz[y];
    }
    te[x] = clk - 1;
}

void dfs(int px, int x, int pe, bool heavy) {
    int h = 0, eh = 0;
    for (const auto& [y, e] : adj[x]) if (y != px) {
        if (sz[h] < sz[y]) h = y, eh = e;
    }
    for (const auto& [y, e] : adj[x]) if (y != px) {
        if (y != h) dfs(x, y, e, false);
    }
    if (h) dfs(x, h, eh, true);

    for (int j : flags[x]) {
        tmp += (tot[j] - 2 * cnt[j]) - 1;
        ++cnt[j];
    }
    for (const auto& [y, _] : adj[x]) if (y != px) {
        if (y == h) continue;
        for (int t = ts[y]; t <= te[y]; ++t) {
            for (int j : flags[ts_inv[t]]) {
                tmp += (tot[j] - 2 * cnt[j]) - 1;
                ++cnt[j];
            }
        }
    }

    ans[pe] = tmp;

    if (!heavy) {
        tmp = 0;
        for (int t = ts[x]; t <= te[x]; ++t) {
            for (int j : flags[ts_inv[t]]) cnt[j] = 0;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    for (int e = 1; e < n; ++e) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y, e);
        adj[y].emplace_back(x, e);
    }
    for (int j = 0; j < m; ++j) {
        cin >> tot[j];
        for (int k = tot[j]; k--;) {
            int x; cin >> x;
            flags[x].emplace_back(j);
        }
    }

    int clk = 0; prep(0, 1, clk);
    sz[0] = -1;
    cnt.fill(0);
    dfs(0, 1, 0, true);

    for (int e = 1; e < n; ++e) cout << ans[e] << '\n';
    return 0;
}
