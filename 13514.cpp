/*
 * Q13514 - LCA by HLD + centroid decomposition
 * Date: 2022.2.20
 */

#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
constexpr int MAXN = 100000;
constexpr int INF = INT_MAX;

vector<int> adj[MAXN+1];
int par[MAXN+1], sz[MAXN+1], dep[MAXN+1],
    ch_id[MAXN+1], ch_dep[MAXN+1], ch_pos[MAXN+1],
    ct_par[MAXN+1];
bool sel[MAXN+1], white[MAXN+1];
priority_queue<pii, vector<pii>, greater<pii>> pqs[MAXN+1];

int dfs_hld(int pu, int u) {
    par[u] = pu;
    sz[u] = 1;
    dep[u] = dep[pu] + 1;
    for (int& v : adj[u]) if (v != pu)
        sz[u] += dfs_hld(u, v);
    return sz[u];
}
void hld(int u, int ci, int cd, int cp) {
    ch_id[u] = ci;
    ch_dep[u] = cd;
    ch_pos[u] = cp;

    int hv = 0;
    for (int& v : adj[u])
        if (v != par[u] && (!hv || sz[v] > sz[hv]))
            hv = v;
    if (hv)
        hld(hv, ci, cd, cp+1);
    for (int& v : adj[u])
        if (v != par[u] && v != hv)
            hld(v, v, cd+1, 0);
}
int dist(int u, int v) {
    int d = dep[u] + dep[v];
    while (ch_id[u] != ch_id[v]) {
        if (ch_dep[u] < ch_dep[v])
            swap(u, v);
        u = par[ch_id[u]];
    }
    int lca = ch_pos[u] < ch_pos[v] ? u : v;
    return d - (dep[lca]<<1);
}

int dfs_ctd(int pu, int u) {
    sz[u] = 1;
    for (int& v : adj[u])
        if (v != pu && !sel[v])
            sz[u] += dfs_ctd(u, v);
    return sz[u];
}
int ct(int pu, int u, int m) {
    bool done = false;
    while (!done) {
        done = true;
        for (int& v : adj[u]) {
            if (v != pu && !sel[v] && sz[v] > m) {
                pu = u, u = v;
                done = false;
                break;
            }
        }
    }
    return u;
}
void ctd(int pc, int u) {
    int n = dfs_ctd(pc, u);
    int c = ct(pc, u, n>>1);
    ct_par[c] = pc;
    sel[c] = true;
    for (int& v : adj[c]) if (!sel[v])
        ctd(c, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    // int N, M, u, v, q, r;

    int N; cin >> N;
    for (int n = 1; n < N; ++n) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs_hld(0, 1);
    hld(1, 1, 0, 0);
    ctd(0, 1);

    int M; cin >> M;
    while (M--) {
        int q, u; cin >> q >> u;
        if (q&1) {
            white[u] = !white[u];
            if (white[u]) {
                int v = u;
                while (v) {
                    pqs[v].emplace(dist(u, v), u);
                    v = ct_par[v];
                }
            }
        }
        else {
            int r = INF;
            int v = u;
            while (v) {
                auto& pq = pqs[v];
                while (!pq.empty() && !white[pq.top().second])
                    pq.pop();
                if (!pq.empty())
                    r = min(r, dist(u, v) + pq.top().first);
                v = ct_par[v];
            }
            cout << (r != INF ? r : -1) << '\n';
        }
    }

    return 0;
}
