/*
 * Q2927 - HLD + Union-find + BIT
 * Date: 2022.7.8
 */

#include<bits/stdc++.h>
using namespace std;

// HLD
vector<vector<int>> adj;
vector<int> hld_par, hld_sz,
            ch_no, ch_dep, ch_idx, ch_len,
            bit_idx;
int hld_dfs1(int pu, int u) {
    hld_par[u] = pu;
    hld_sz[u]  = 1;
    for (int& v : adj[u]) if (v != pu)
        hld_sz[u] += hld_dfs1(u, v);
    return hld_sz[u];
}
void hld_dfs2(int u, int cn, int cd, int& bi) {
    ch_no[u]   = cn;
    ch_dep[u]  = cd;
    ch_idx[u]  = ch_len[cn]++;
    bit_idx[u] = bi++;

    int hv = 0;
    for (int& v : adj[u])
        if (v != hld_par[u] && (hld_sz[hv] < hld_sz[v]))
            hv = v;
    if (hv)
        hld_dfs2(hv, cn, cd, bi);
    for (int& v : adj[u])
        if (v != hld_par[u] && v != hv)
            hld_dfs2(v, v, cd+1, bi);
}

// Union-find
vector<int> uf_arr;
int find(int x) {
    if (uf_arr[x] < 0)
        return x;
    return uf_arr[x] = find(uf_arr[x]);
}
bool connected(int x, int y) {
    return find(x) == find(y);
}
bool link(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return false;
    if (uf_arr[x] < uf_arr[y])
        uf_arr[y] = x;
    else {
        if (uf_arr[x] == uf_arr[y])
            uf_arr[y]--;
        uf_arr[x] = y;
    }
    return true;
}

// BIT
class BIT {
    int sz;
    vector<int> tree;
    int lsb(int n) { return n & -n; }
public:
    BIT(vector<int>& data) {
        sz = data.size();
        tree.resize(sz);
        for (int i = 1; i < sz; ++i)
            tree[bit_idx[i]] = data[i];
        for (int i = 1; i < sz; ++i) {
            int j = i + lsb(i);
            if (j < sz)
                tree[j] += tree[i];
        }
    }
    void update(int i, int v) {
        int cur = query(i, i);
        for (; i < sz; i += lsb(i))
            tree[i] += (v - cur);
    }
    int query(int i, int j) {
        int ret = 0;
        i--;
        for (; j > i; j -= lsb(j))
            ret += tree[j];
        for (; i > j; i -= lsb(i))
            ret -= tree[i];
        return ret;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> data(N+1);
    for (int n = 1; n <= N; ++n)
        cin >> data[n];

    adj.resize(N+1);
    uf_arr.resize(N+1, -1);

    int M; cin >> M;
    struct query { int op, a, b; };
    vector<query> queries(M);

    for (auto& q : queries) {
        string str;
        cin >> str >> q.a >> q.b;
        switch (str[0]) {
            case 'b':
                q.op = 0;
                if (link(q.a, q.b)) {
                    adj[q.a].emplace_back(q.b);
                    adj[q.b].emplace_back(q.a);
                }
                break;
            case 'p':
                q.op = 1;
                break;
            case 'e':
                q.op = 2;
        }
    }

    hld_par.resize(N+1);
    hld_sz .resize(N+1);
    ch_no  .resize(N+1);
    ch_dep .resize(N+1);
    ch_idx .resize(N+1);
    ch_len .resize(N+1);
    bit_idx.resize(N+1);

    for (int u = 1; u <= N; ++u) if (!hld_sz[u])
        hld_dfs1(0, u);
    int bi = 1;
    for (int u = 1; u <= N; ++u) if (!ch_no[u])
        hld_dfs2(u, u, 0, bi);

    fill(uf_arr.begin(), uf_arr.end(), -1);
    BIT bit(data);

    for (const auto& q : queries) {
        int a = q.a, b = q.b;
        switch (q.op) {
            case 0:
                cout << (link(a, b) ? "yes\n" : "no\n");
                break;
            case 1:
                bit.update(bit_idx[a], b);
                break;
            case 2:
                if (connected(a, b)) {
                    int ans = 0;
                    while (ch_no[a] != ch_no[b]) {
                        if (ch_dep[a] > ch_dep[b])
                            swap(a, b);
                        ans += bit.query(bit_idx[ch_no[b]], bit_idx[b]);
                        b = hld_par[ch_no[b]];
                    }
                    if (ch_idx[a] > ch_idx[b])
                        swap(a, b);
                    ans += bit.query(bit_idx[a], bit_idx[b]);
                    cout << ans << '\n';
                }
                else cout << "impossible\n";
        }
    }

    return 0;
}
