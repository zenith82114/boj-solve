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
    chNo[MAXN+1], chDep[MAXN+1], chIdx[MAXN+1], chLen[MAXN+1],
    stIdx[MAXN+1];

class SegTree {
    int N;
    vector<int> A;
    int ceilPow2(int n) {
        if (n & (n-1)) {
            for (int i=1; i<32; i<<=1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }
    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1|1; }
    int queryUtil(int n, int l, int r, int i, int j) {
        int m = (l+r)>>1;
        if (l > j || r < i)
            return 0;
        if (l < i || r > j)
            return max(
                queryUtil(lc(n), l, m, i, j),
                queryUtil(rc(n), m+1, r, i, j)
            );
        return A[n];
    }
public:
    void init(int _N) {
        N = _N;
        A.assign(ceilPow2(N)<<1, 0);
    }
    void update(int i, int w) {
        int n=1, l=0, r=N-1, m;
        while (l != r) {
            m = (l+r)>>1;
            if (m < i)
                n = rc(n), l = m+1;
            else
                n = lc(n), r = m;
        }
        A[n] = w;
        while (n > 1) {
            m = max(A[n], A[n^1]);
            if (A[n>>1] != m)
                A[n>>1] = m, n >>= 1;
            else break;
        }
    }
    int query(int i, int j) {
        if (i > j)
            return 0;
        return queryUtil(1, 0, N-1, i, j);
    }
} segt;

int dfs(int pu, int u) {
    par[u] = pu;
    sz[u] = 1;
    for (int& v : adj[u])
        if (v != pu)
            sz[u] += dfs(u, v);
    return sz[u];
}

void hld(int u, int cn, int cd, int& ti) {
    chNo[u] = cn;
    chDep[u] = cd;
    chIdx[u] = chLen[cn]++;
    stIdx[u] = ti++;

    int hv = 0;
    for (int& v : adj[u])
        if (v != par[u] && (!hv || sz[v] > sz[hv]))
            hv = v;
    if (hv)
        hld(hv, cn, cd, ti);
    for (int& v : adj[u])
        if (v != par[u] && v != hv)
            hld(v, v, cd+1, ti);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M, i, u, v, w, q, r;

    cin >> N;
    for (i=1; i<N; i++) {
        cin >> u >> v >> w;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        edges[i] = { u, v, w };
    }

    dfs(0, 1);
    i = 0;
    hld(1, 1, 0, i);
    segt.init(N);
    for (i=1; i<N; i++) {
        auto& e = edges[i];
        if (chNo[e.u] != chNo[e.v]) {
            if (chDep[e.u] > chDep[e.v])
                swap(e.u, e.v);
        }
        else if (chIdx[e.u] > chIdx[e.v])
            swap(e.u, e.v);
        segt.update(stIdx[e.v], e.w);
    }

    cin >> M;
    while (M--) {
        cin >> q;
        if (q&1) {
            cin >> i >> w;
            segt.update(stIdx[edges[i].v], w);
        }
        else {
            cin >> u >> v;
            r = 0;
            while (chNo[u] != chNo[v]) {
                if (chDep[u] > chDep[v])
                    swap(u, v);
                r = max(r, segt.query(stIdx[chNo[v]], stIdx[v]));
                v = par[chNo[v]];
            }
            if (chIdx[u] > chIdx[v])
                swap(u, v);
            r = max(r, segt.query(stIdx[u]+1, stIdx[v]));
            cout << r << '\n';
        }
    }

    return 0;
}
