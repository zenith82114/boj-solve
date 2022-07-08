/*
 * Q5820 - Centroid DnC
 * Date: 2022.7.8
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = INT_MAX>>1;

struct Edge {
    int v, d;
    Edge(int v_, int d_): v(v_), d(d_) {}
};
vector<vector<Edge>> adj;
vector<int> sz, min_dep, dirty;
vector<bool> is_ct;

int dfs_sz(int pu, int u) {
    sz[u] = 1;
    for (const auto& e : adj[u])
        if (e.v != pu && !is_ct[e.v])
            sz[u] += dfs_sz(u, e.v);
    return sz[u];
}
int ct(int pu, int u, int m) {
    for (const auto& e : adj[u])
        if (e.v != pu && !is_ct[e.v] && sz[e.v] > m)
            return ct(u, e.v, m);
    return u;
}
int dfs_calc(int pu, int u, int K, int dep, int dist) {
    int ret = INF;
    if (dist <= K) {
        ret = min(ret, dep + min_dep[K - dist]);
        for (const auto& e : adj[u])
            if (e.v != pu && !is_ct[e.v])
                ret = min(ret, dfs_calc(
                    u, e.v, K, dep+1, dist + e.d));
    }
    return ret;
}
void dfs_upd(int pu, int u, int K, int dep, int dist) {
    if (dist <= K) {
        min_dep[dist] = min(min_dep[dist], dep);
        dirty.emplace_back(dist);
        for (const auto& e : adj[u])
            if (e.v != pu && !is_ct[e.v])
                dfs_upd(u, e.v, K, dep+1, dist + e.d);
    }
}
int ctd_dnc(int u, int K) {
    int c = ct(-1, u, dfs_sz(-1, u)>>1);
    is_ct[c] = true;

    while (!dirty.empty()) {
        min_dep[dirty.back()] = INF;
        dirty.pop_back();
    }

    int ret = INF;
    for (const auto& e : adj[c]) if (!is_ct[e.v]) {
        ret = min(ret, dfs_calc(c, e.v, K, 1, e.d));
        dfs_upd(c, e.v, K, 1, e.d);
    }
    for (const auto& e : adj[c]) if (!is_ct[e.v])
        ret = min(ret, ctd_dnc(e.v, K));

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

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
