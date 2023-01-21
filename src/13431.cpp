/*
 * Q13431 - Centroid decomposition
 * Date: 2023.1.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int MAXN = 100'000;
constexpr int MAXLGN = 16;

vector<pair<int, int>> tree[MAXN];

/* LCA by RMQ */
vector<int> lvl;
int ind[MAXN], rind[MAXN <<1];
int tbl[MAXLGN +2][MAXN <<1];
i64 dep[MAXN];

/* Centroid decomposition */
int sz[MAXN], ct_par[MAXN];
bool sel[MAXN];

void dfs_lca(int pu, int u, int k) {
    ind[u] = lvl.size();
    rind[ind[u]] = u;
    lvl.emplace_back(k);
    for (const auto& [v, w] : tree[u]) if (v != pu) {
        dep[v] = dep[u] + w;
        dfs_lca(u, v, k +1);
        rind[lvl.size()] = u;
        lvl.emplace_back(k);
    }
}
i64 dist(int u, int v) {
    int l = ind[u], r = ind[v];
    if (l > r) swap(l, r);

    int i = 0, k = 1;
    for (; k<<1 <= r - l + 1; ++i, k <<= 1);

    int& x1 = tbl[i][l];
    int& x2 = tbl[i][r - k +1];
    int& lca = rind[lvl[x1] < lvl[x2]? x1 : x2];
    return dep[u] + dep[v] - (dep[lca]<<1);
}

int dfs_ctd(int pu, int u) {
    sz[u] = 1;
    for (const auto& [v, w] : tree[u])
        if (v != pu && !sel[v])
            sz[u] += dfs_ctd(u, v);
    return sz[u];
}
int ct(int pu, int u, int m) {
    for (const auto& [v, w] : tree[u])
        if (v != pu && !sel[v] && sz[v] > m)
            return ct(u, v, m);
    return u;
}
void ctd(int pc, int u) {
    int m = dfs_ctd(pc, u);
    int c = ct(pc, u, m>>1);
    ct_par[c] = pc;
    sel[c] = true;
    for (const auto& [v, w] : tree[c])
        if (!sel[v]) ctd(c, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, Q; cin >> N >> Q;
    for (int n = 1; n < N; ++n) {
        int u, v, w; cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    dep[0] = 0ll;
    dfs_lca(-1, 0, 0);

    const int lgN = [] (int n) {
        int k = 0;
        while (n >>= 1) k++;
        return k;
    } (N);

    const int M = (N<<1) -1;
    for (int j = 0; j < M; ++j) tbl[0][j] = j;

    for (int i = 1; i <= lgN +1; ++i)
    for (int j = 0; j + (1<<i) <= M; ++j) {
        int& x1 = tbl[i-1][j];
        int& x2 = tbl[i-1][j + (1<<(i-1))];
        tbl[i][j] = lvl[x1] < lvl[x2]? x1 : x2;
    }

    ct_par[0] = -1;
    ctd(-1, 0);

    vector<bool> blue(N);
    vector<int> cnt(N);
    vector<i64> sum(N);
    vector<map<int, i64>> sum_under(N);
    for (int c = 0; c < N; ++c) if (ct_par[c] != -1)
        sum_under[ct_par[c]].emplace(c, 0ll);

    while (Q--) {
        int q, u; cin >> q >> u;

        if (q & 1) {
            if (blue[u]) continue;
            blue[u] = true;
            cnt[u]++;
            for (int c = u; ct_par[c] != -1; c = ct_par[c]) {
                int& pc = ct_par[c];
                i64 d = dist(pc, u);
                cnt[pc]++;
                sum[pc] += d;
                sum_under[pc][c] += d;
            }
        }
        else {
            i64 ans = sum[u];
            for (int c = u; ct_par[c] != -1; c = ct_par[c]) {
                int& pc = ct_par[c];
                ans += sum[pc] - sum_under[pc][c] + (cnt[pc] - cnt[c]) * dist(pc, u);
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
