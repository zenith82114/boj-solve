/*
 * Q8872 - Diameter and radius of tree
 * Date: 2022.12.29
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> forest;
vector<bool> visited;
vector<int> h, f;

pair<int, int> farthest(int pu, int u) {
    int x = u;
    int d = 0;
    for (const auto& [v, w] : forest[u]) if (v != pu) {
        auto [y, d1] = farthest(u, v);
        if (d < w + d1) {
            x = y;
            d = w + d1;
        }
    }
    return make_pair(x, d);
}

void dfs_hf(int pu, int u) {
    visited[u] = true;
    h[u] = 0;
    int m1 = 0, m2 = 0;
    for (const auto& [v, w] : forest[u]) if (v != pu) {
        dfs_hf(u, v);
        int m = w + h[v];
        h[u] = max(h[u], m);
        if (m >= m1) { m2 = m1; m1 = m; }
        else if (m > m2) m2 = m;
    }
    for (const auto& [v, w] : forest[u]) if (v != pu)
        f[v] = w + (w + h[v] == m1? m2 : m1);
}

int dfs_ge(int pu, int u, int gu, int eu) {
    int r = eu;
    for (const auto& [v, w] : forest[u]) if (v != pu) {
        int gv = max(f[v], w + gu);
        int ev = max(gv, h[v]);
        r = min(r, dfs_ge(u, v, gv, ev));
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, L; cin >> N >> M >> L;
    forest.resize(N);
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        forest[u].emplace_back(v, w);
        forest[v].emplace_back(u, w);
    }

    visited.resize(N, false);
    h.resize(N);
    f.resize(N);
    int d1 = 0;
    int r1 = -1, r2 = -1, r3 = -1;
    for (int u = 0; u < N; ++u) if (!visited[u]) {
        // diameter
        auto p = farthest(-1, u);
        auto q = farthest(-1, p.first);
        d1 = max(d1, q.second);

        // radius
        dfs_hf(-1, u);
        int r = dfs_ge(-1, u, 0, h[u]);
        if (r >= r1) { r3 = r2; r2 = r1; r1 = r; }
        else if (r >= r2) { r3 = r2; r2 = r; }
        else if (r > r3) r3 = r;
    }

    int ans = d1;
    if (r2 != -1) ans = max(ans, r1 + r2 + L);
    if (r3 != -1) ans = max(ans, r2 + r3 + L + L);
    cout << ans << endl;

    return 0;
}
