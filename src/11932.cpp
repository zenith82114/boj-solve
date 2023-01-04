/*
 * Q11932 - Persistent segment tree + LCA
 * Date: 2023.1.2
 */

#include<bits/stdc++.h>
using namespace std;

class PersistentSegTree {
    class Compressor {
        vector<int> ar;
    public:
        Compressor(const vector<int>& data) {
            ar = data;
            sort(ar.begin(), ar.end());
        }
        int encode(int x) {
            return lower_bound(ar.begin(), ar.end(), x) - ar.begin();
        }
        int decode(int i) { return ar[i]; }
    } comp;

    struct Node {
        int l = -1, r = -1, val = 0;
    };
    vector<int> roots;
    vector<Node> nodes;
    vector<int> depth;
    vector<vector<int>> parent;
    int N, lgN;

    void init_util(int n, int s, int e) {
        if (s == e) return;
        nodes[n].l = nodes.size();
        nodes[n].r = nodes.size() + 1;
        nodes.emplace_back();
        nodes.emplace_back();
        int m = (s + e)>>1;
        init_util(nodes[n].l, s, m);
        init_util(nodes[n].r, m+1, e);
    }
    void insert_util(int pn, int n, int s, int e, int i) {
        if (s == e) {
            nodes[n].val++;
            return;
        }
        int m = (s + e)>>1;
        if (i <= m) {
            nodes[n].l = nodes.size();
            nodes[n].r = nodes[pn].r;
            nodes.emplace_back();
            insert_util(nodes[pn].l, nodes[n].l, s, m, i);
        }
        else {
            nodes[n].l = nodes[pn].l;
            nodes[n].r = nodes.size();
            nodes.emplace_back();
            insert_util(nodes[pn].r, nodes[n].r, m+1, e, i);
        }
        nodes[n].val = nodes[nodes[n].l].val + nodes[nodes[n].r].val;
    }
    void dfs(int pu, int u, const vector<vector<int>>& tree, const vector<int>& weights) {
        for (const int& v : tree[u]) if (v != pu) {
            roots[v] = nodes.size();
            nodes.emplace_back();
            insert_util(roots[u], roots[v], 0, N-1, comp.encode(weights[v]));
            depth[v] = depth[u] + 1;
            parent[0][v] = u;
            dfs(u, v, tree, weights);
        }
    }
    int query_util(int n1, int n2, int n3, int n4, int s, int e, int k) {
        if (s == e) return s;
        int m = (s + e)>>1;
        int d = nodes[nodes[n1].l].val + nodes[nodes[n2].l].val
                - nodes[nodes[n3].l].val - nodes[nodes[n4].l].val;
        if (k <= d)
            return query_util(nodes[n1].l, nodes[n2].l, nodes[n3].l, nodes[n4].l, s, m, k);
        else
            return query_util(nodes[n1].r, nodes[n2].r, nodes[n3].r, nodes[n4].r, m+1, e, k - d);
    }
public:
    PersistentSegTree(const vector<vector<int>>& tree, const vector<int>& weights)
    : comp(weights), N(tree.size() - 1) {
        roots.resize(N+1, 0);
        nodes.emplace_back();
        init_util(0, 0, N-1);

        roots[1] = nodes.size();
        nodes.emplace_back();
        insert_util(roots[0], roots[1], 0, N-1, comp.encode(weights[1]));

        depth.resize(N+1, 0);
        lgN = [](int n) {
            int k = 0;
            for (; n > 1; n >>= 1) k++;
            return k;
        }(N);
        parent.resize(lgN+1, vector<int>(N+1, -1));
        dfs(0, 1, tree, weights);

        for (int i = 1; i <= lgN; ++i)
        for (int u = 2; u <= N; ++u) if (parent[i-1][u] > 0)
            parent[i][u] = parent[i-1][parent[i-1][u]];
    }
    int query(int u, int v, int k) {
        int a = u, b = v;
        if (depth[a] < depth[b]) swap(a, b);
        for (int d = depth[a] - depth[b], k = 0; d; d >>= 1, ++k)
            if (d & 1) a = parent[k][a];

        if (a != b) {
            for (int k = lgN; k > -1; --k) if (parent[k][a] != parent[k][b]) {
                a = parent[k][a];
                b = parent[k][b];
            }
            a = parent[0][a];
        }
        int pa = a != 1? parent[0][a] : 0;
        return comp.decode(query_util(
            roots[u], roots[v], roots[a], roots[pa], 0, N-1, k
        ));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<int> weights(N+1);
    weights[0] = INT_MAX;
    for (int i = 1; i <= N; ++i) cin >> weights[i];

    vector<vector<int>> tree(N+1);
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    PersistentSegTree psegt(tree, weights);
    while (M--) {
        int u, v, k; cin >> u >> v >> k;
        cout << psegt.query(u, v, k) << '\n';
    }

    return 0;
}
