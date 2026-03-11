/*
 * Q28254a - tree compression, difference array
 * Date: 2026.3.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 5e5 +4;

vector<int> g[MAXN];
array<int, MAXN> ord, dep, sz;
array<i64, MAXN> diff;
int rmq[20][2 * MAXN] {};
bitset<MAXN> chk;

void dfs_prep(int px, int x) {
    static int clk = 0;
    ord[x] = clk;
    rmq[0][clk++] = x;
    for (int y : g[x]) if (y != px) {
        dep[y] = dep[x] + 1;
        dfs_prep(x, y);
        rmq[0][clk++] = x;
    }
}

int lca(int x, int y) {
    int l = ord[x], r = ord[y]; if (l > r) swap(l, r);
    int n = r - l + 1;
    int i = 19; while (~n & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return dep[x1] < dep[x2] ? x1 : x2;
}

void dfs_psum(int px, int x) {
    for (int y : g[x]) if (y != px) dfs_psum(x, y);
    diff[px] += diff[x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<pair<int, int> > edges(n - 1);
    for (auto& [x, y] : edges) {
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dep[1] = 0;
    dfs_prep(0, 1);

    for (int i = 1; i < 20; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*n - 1; ++j) {
        int x1 = rmq[i - 1][j], x2 = rmq[i - 1][j + (1<<i>>1)];
        rmq[i][j] = dep[x1] < dep[x2] ? x1 : x2;
    }

    sz.fill(0);
    diff.fill(0);

    while (m--) {
        int k; cin >> k;
        if (!k) continue;
        vector<int> inp(k);
        for (int& x : inp) cin >> x, chk.set(x);
        sort(inp.begin(), inp.end(), [] (int x, int y) { return ord[x] < ord[y]; });

        auto virtual_edge = [&k] (int u, int p) {
            i64 delta = (i64)sz[u] * (k - sz[u]);
            diff[u] += delta;
            diff[p] -= delta;
            sz[p] += sz[u];
            sz[u] = 0;
        };

        auto it = inp.begin();
        vector<int> stk { *it };
        sz[*(it++)] = 1;
        for (; it < inp.end(); ++it) {
            int x = *it;
            int w = lca(stk.back(), x);

            while (stk.size() > 1 && dep[stk[stk.size() - 2]] >= dep[w]) {
                int u = stk.back(); stk.pop_back();
                int p = stk.back();
                virtual_edge(u, p);
            }
            if (stk.back() != w) {
                int u = stk.back(); stk.pop_back();
                sz[w] = 0;  // w is not in inp
                virtual_edge(u, w);
                stk.push_back(w);
            }

            stk.push_back(x);
            sz[x] = 1;
        }
        while (stk.size() > 1) {
            int u = stk.back(); stk.pop_back();
            int p = stk.back();
            virtual_edge(u, p);
        }
        sz[stk[0]] = 0;
        for (int& x : inp) chk.reset(x);
    }

    dfs_psum(0, 1);

    for (const auto& [x, y] : edges) {
        cout << (dep[x] < dep[y] ? diff[y] : diff[x]) << '\n';
    }

    return 0;
}
