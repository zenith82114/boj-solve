/*
 * Q13510 - Heavy-light decomposition
 * Date: 2022.2.19
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 100000;

struct Edge { int u, v, w; } edges[MAXN];
vector<int> adj[MAXN+1];
int par[MAXN+1], sz[MAXN+1],
    ch_id[MAXN+1], ch_dep[MAXN+1], ch_pos[MAXN+1],
    st_idx[MAXN+1];

class seg_tree {
    int N;
    vector<int> A;
    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1|1; }
    int query_util(int n, int l, int r, int i, int j) {
        int m = (l+r)>>1;
        if (l > j || r < i)
            return 0;
        if (l < i || r > j)
            return max(
                query_util(lc(n), l, m, i, j),
                query_util(rc(n), m+1, r, i, j)
            );
        return A[n];
    }
public:
    void init(int _N) {
        N = _N;
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.assign(sz<<1, 0);
    }
    void update(int i, int w) {
        int n = 1, l = 0, r = N-1;
        while (l != r) {
            int m = (l+r)>>1;
            if (m < i)
                n = rc(n), l = m+1;
            else
                n = lc(n), r = m;
        }
        A[n] = w;
        while (n > 1) {
            int m = max(A[n], A[n^1]);
            if (A[n>>1] != m)
                A[n>>1] = m, n >>= 1;
            else break;
        }
    }
    int query(int i, int j) {
        if (i > j)
            return 0;
        return query_util(1, 0, N-1, i, j);
    }
} segt;

int dfs(int pu, int u) {
    par[u] = pu;
    sz[u] = 1;
    for (int& v : adj[u]) if (v != pu)
        sz[u] += dfs(u, v);
    return sz[u];
}

void hld(int u, int ci, int cd, int cp, int& ti) {
    ch_id[u] = ci;
    ch_dep[u] = cd;
    ch_pos[u] = cp;
    st_idx[u] = ti++;

    int hv = 0;
    for (int& v : adj[u])
        if (v != par[u] && (!hv || sz[v] > sz[hv]))
            hv = v;
    if (hv)
        hld(hv, ci, cd, cp+1, ti);
    for (int& v : adj[u]) if (v != par[u] && v != hv)
        hld(v, v, cd+1, 0, ti);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    for (int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        edges[i] = { u, v, w };
    }

    dfs(0, 1);
    int id = 0;
    hld(1, 1, 0, 0, id);

    segt.init(N);
    for (int i = 1; i < N; ++i) {
        auto& e = edges[i];
        if (ch_id[e.u] != ch_id[e.v]) {
            if (ch_dep[e.u] > ch_dep[e.v])
                swap(e.u, e.v);
        }
        else if (ch_pos[e.u] > ch_pos[e.v])
            swap(e.u, e.v);
        segt.update(st_idx[e.v], e.w);
    }

    int M; cin >> M;
    while (M--) {
        int q; cin >> q;
        if (q&1) {
            int i, w; cin >> i >> w;
            segt.update(st_idx[edges[i].v], w);
        }
        else {
            int u, v; cin >> u >> v;
            int r = 0;
            while (ch_id[u] != ch_id[v]) {
                if (ch_dep[u] > ch_dep[v])
                    swap(u, v);
                r = max(r, segt.query(st_idx[ch_id[v]], st_idx[v]));
                v = par[ch_id[v]];
            }
            if (ch_pos[u] > ch_pos[v])
                swap(u, v);
            r = max(r, segt.query(st_idx[u]+1, st_idx[v]));
            cout << r << '\n';
        }
    }

    return 0;
}
