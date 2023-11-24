/*
 * Q15480 - LCA
 * Date: 2023.11.24
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100'001] {};
int rmq[20][200'000] {};
int dep[100'001] {};
int st[100'001] {};

void dfs(int px, int x, int& clk) {
    st[x] = clk;
    rmq[0][clk++] = x;
    for (int y : adj[x]) if (y != px) {
        dep[y] = dep[x] + 1;
        dfs(x, y, clk);
        rmq[0][clk++] = x;
    }
}

int lca(int x, int y) {
    int l = st[x], r = st[y]; if (l > r) swap(l, r);
    int n = r - l + 1;
    int i = 17; while (~n & (1<<i)) --i;
    int x1 = rmq[i][l], x2 = rmq[i][r - (1<<i) + 1];
    return dep[x1] < dep[x2]? x1 : x2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    int clk = 0; dfs(0, 1, clk);
    for (int i = 1; i < 20; ++i)
    for (int j = 0; j + (1<<i>>1) < 2*n; ++j) {
        int x1 = rmq[i-1][j], x2 = rmq[i-1][j + (1<<i>>1)];
        rmq[i][j] = dep[x1] < dep[x2]? x1 : x2;
    }

    int m; cin >> m;
    while (m--) {
        int r, x, y; cin >> r >> x >> y;
        cout << (lca(r, x) ^ lca(r, y) ^ lca(x, y)) << '\n';
    }

    return 0;
}
