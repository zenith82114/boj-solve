/*
 * Q5820 - Centroid DnC
 * Date: 2022.7.8
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = INT_MAX>>1;

struct Edge {
    int v, d;
    Edge(int v, int d): v(v), d(d) {}
};
vector<vector<Edge>> adj;
vector<int> sz, min_dep, dirty;
vector<bool> is_ct;

int dfs_sz(int pu, int u) {
    sz[u] = 1;
    for (const auto& [v, d] : adj[u])
        if (v != pu && !is_ct[v])
            sz[u] += dfs_sz(u, v);
    return sz[u];
}
int ct(int pu, int u, int m) {
    for (const auto& [v, d] : adj[u])
        if (v != pu && !is_ct[v] && sz[v] > m)
            return ct(u, v, m);
    return u;
}
int dfs_calc(int pu, int u, int K, int dep, int dist) {
    int ret = INF;
    if (dist <= K) {
        ret = min(ret, dep + min_dep[K - dist]);
        for (const auto& [v, d] : adj[u])
            if (v != pu && !is_ct[v])
                ret = min(ret, dfs_calc(u, v, K, dep+1, dist + d));
    }
    return ret;
}
void dfs_upd(int pu, int u, int K, int dep, int dist) {
    if (dist <= K) {
        min_dep[dist] = min(min_dep[dist], dep);
        dirty.emplace_back(dist);
        for (const auto& [v, d] : adj[u])
            if (v != pu && !is_ct[v])
                dfs_upd(u, v, K, dep+1, dist + d);
    }
}
int ctd_dnc(int u, int K) {
    int c = ct(-1, u, dfs_sz(-1, u)>>1);
    is_ct[c] = true;

    for (const int& x : dirty) min_dep[x] = INF;
    dirty.clear();

    int ret = INF;
    for (const auto& [v, d] : adj[c]) if (!is_ct[v]) {
        ret = min(ret, dfs_calc(c, v, K, 1, d));
        dfs_upd(c, v, K, 1, d);
    }
    for (const auto& [v, d] : adj[c]) if (!is_ct[v])
        ret = min(ret, ctd_dnc(v, K));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, K; cin >> N >> K;
    adj.resize(N);
    for (int n = 0; n < N-1; n++) {
        int i, j, d; cin >> i >> j >> d;
        adj[i].emplace_back(j, d);
        adj[j].emplace_back(i, d);
    }

    sz.resize(N);
    is_ct.resize(N, false);
    min_dep.resize(K+1, INF);
    min_dep[0] = 0;
    int ans = ctd_dnc(0, K);
    cout << (ans != INF ? ans : -1) << '\n';

    return 0;
}
