/*
 * Q13511 - Edge sum and k-th vertex on a tree path using LCA
 * Date: 2021.8.25
 */

#include<iostream>
#include<bitset>
#include<tuple>
#include<vector>
using namespace std;
#define ll long long
constexpr int maxN = 100000, maxlgN = 16;
int N, lgN;

vector<pair<int, int>> tree[maxN + 1];
int parent[maxlgN + 1][maxN + 1];
ll dist[maxlgN + 1][maxN + 1];
int depth[maxN + 1];
bitset<maxN + 1> visited;

void dfs(int v, int pv) {
    visited.set(v);
    parent[0][v] = pv;
    depth[v] = depth[pv] + 1;
    for (const auto& [u, w] : tree[v]) {
        if (u != pv && !visited.test(u)) {
            dist[0][u] = w;
            dfs(u, v);
        }
    }
}

int lca(int u, int v, ll& d) {
    ll L = 0;
    if (depth[u] < depth[v])
        swap(u, v);
    for (int H = depth[u] - depth[v], i = 0; H; H >>= 1, ++i)
        if (H & 1) {
            L += dist[i][u];
            u = parent[i][u];
        }
    if (u != v) {
        for (int i = lgN; i >= 0; --i)
            if (parent[i][u] != parent[i][v]) {
                L += dist[i][u] + dist[i][v];
                u = parent[i][u];
                v = parent[i][v];
            }
        d = L + dist[0][u] + dist[0][v];
        return parent[0][u];
    }
    else {
        d = L;
        return u;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    lgN = [](int n) {
        int k = 0;
        while (n >>= 1) k++;
        return k;
    }(N);
    for (int n = 1; n < N; ++n) {
        int u, v, w; cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    dfs(1, 0);
    for (int i = 0; i < lgN; ++i)
    for (int u = 1; u <= N; ++u) {
        int& v = parent[i][u];
        if (v != 0) {
            parent[i + 1][u] = parent[i][v];
            dist[i + 1][u] = dist[i][u] + dist[i][v];
        }
    }

    int M; cin >> M;
    while (M--) {
        int c, u, v; cin >> c >> u >> v;
        ll d;
        int w = lca(u, v, d);
        if (c & 1)
            cout << d << '\n';
        else {
            int k; cin >> k;
            k--;
            int hu = depth[u] - depth[w];
            int hv = depth[v] - depth[w];
            if (k < hu) {
                for (int i = 0; k; k >>= 1, ++i)
                    if (k & 1) u = parent[i][u];
                cout << u << '\n';
            } else {
                k = hu + hv - k;
                for (int i = 0; k; k >>= 1, ++i)
                    if (k & 1) v = parent[i][v];
                cout << v << '\n';
            }
        }
    }

    return 0;
}
