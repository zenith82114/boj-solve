/*
 * Q13309 - Heavy-light decomposition
 * Date: 2022.12.22
 */

#include<bits/stdc++.h>
using namespace std;

struct HLD {
    static const int ROOT = 1;
    vector<int> par, sz;
    vector<int> ch_id, ch_dep, ch_pos;
    vector<int> et;
    void dfs(int pu, int u, const vector<vector<int>>& tree) {
        par[u] = pu;
        sz[u] = 1;
        for (const int& v : tree[u]) if (v != pu) {
            dfs(u, v, tree);
            sz[u] += sz[v];
        }
    }
    void run(int u, int ci, int cd, int cp, int& e, const vector<vector<int>>& tree) {
        ch_id[u] = ci;
        ch_dep[u] = cd;
        ch_pos[u] = cp;
        et[u] = e++;

        int hv = 0;
        for (const int& v : tree[u]) if (v != par[u] && sz[hv] < sz[v])
            hv = v;
        if (hv != 0)
            run(hv, ci, cd, cp+1, e, tree);
        for (const int& v : tree[u]) if (v != par[u] && v != hv)
            run(v, v, cd+1, 0, e, tree);
    }
    HLD(const vector<vector<int>>& tree) {
        int N = tree.size();
        par.resize(N);
        sz. resize(N);
        ch_id .resize(N);
        ch_dep.resize(N);
        ch_pos.resize(N);
        et.resize(N);

        dfs(0, ROOT, tree); // sz[0] == 0
        int e = 0;
        run(ROOT, 1, 0, 0, e, tree);
    }
};

class SegTree {
    int N;
    vector<bool> arr;
public:
    SegTree(int n) {
        for (N = 1; N < n; N <<= 1);
        arr.resize(N<<1, true);
    }
    void update(int i) {
        i |= N;
        arr[i] = false;
        for (; i > 1; i >>= 1)
            arr[i>>1] = arr[i] && arr[i^1];
    }
    bool query(int i, int j) {
        bool ans = true;
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if (i&1)    { ans = ans && arr[i]; ++i; }
            if ((~j)&1) { ans = ans && arr[j]; --j; }
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, Q; cin >> N >> Q;
    vector<vector<int>> tree(N+1);
    for (int i = 2; i <= N; ++i) {
        int p; cin >> p;
        tree[p].emplace_back(i);
    }

    HLD hld(tree);
    SegTree segt(N);

    while (Q--) {
        int u, v, d; cin >> u >> v >> d;
        int x = u, y = v;
        bool r = true;

        while (hld.ch_id[x] != hld.ch_id[y]) {
            if (hld.ch_dep[x] > hld.ch_dep[y]) swap(x, y);
            r = r && segt.query(hld.et[hld.ch_id[y]], hld.et[y]);
            y = hld.par[hld.ch_id[y]];
        }
        if (hld.ch_pos[x] > hld.ch_pos[y]) swap(x, y);
        if (x != y)
            r = r && segt.query(hld.et[x] + 1, hld.et[y]);
        cout << (r? "YES" : "NO") << '\n';

        if (d) segt.update(hld.et[r? u : v]);
    }

    return 0;
}
