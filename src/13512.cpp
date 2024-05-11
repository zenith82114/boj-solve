/*
 * Q13512 - HLD + set
 * Date: 2024.5.11
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100005;

array<vector<int>, MAXN> tree;
array<int, MAXN> par, sz, ch_no, vis, ivis;
set<int> black_set[MAXN];

int dfs(int px, int x) {
    par[x] = px;
    sz[x] = 1;
    for (int y : tree[x]) if (y != px) sz[x] += dfs(x, y);
    return sz[x];
}
void hld(int x, int cn, int& clk) {
    ch_no[x] = cn;
    vis[x] = clk++;
    ivis[vis[x]] = x;

    int hy = 0;
    for (int y : tree[x]) {
        if (y != par[x] && sz[hy] < sz[y]) hy = y;
    }
    if (hy) hld(hy, cn, clk);
    for (int y : tree[x]) {
        if (y != par[x] && y != hy) hld(y, y, clk);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        tree[x].emplace_back(y);
        tree[y].emplace_back(x);
    }
    sz[0] = 0;
    dfs(0, 1);
    int clk = 0; hld(1, 1, clk);

    int m; cin >> m;
    while (m--) {
        int op, x; cin >> op >> x;
        if (op&1) {
            auto& s = black_set[ch_no[x]];
            auto f = s.find(vis[x]);
            if (f == s.end()) s.emplace_hint(f, vis[x]);
            else s.erase(f);
        } else {
            int y = -1;
            for (; x > 0; x = par[ch_no[x]]) {
                auto& s = black_set[ch_no[x]];
                if (s.size() && *s.begin() <= vis[x]) {
                    y = ivis[*s.begin()];
                }
            }
            cout << y << '\n';
        }
    }

    return 0;
}
