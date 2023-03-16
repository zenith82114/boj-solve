/*
 * Q1626 - MST + LCA
 * Date: 2023.3.16
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class UnionFind {
    vector<int> ar;
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
public:
    UnionFind(int sz): ar(sz, -1) {}
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;

        if (ar[x] == ar[y]) ar[x]--;
        if (ar[x] < ar[y]) ar[y] = x;
        else ar[x] = y;
        return true;
    }
};

vector<vector<ii> > mst;
vector<vector<pair<int, ii> > > sptb;
vector<int> dep;

void dfs(int pu, int u) {
    for (auto& [v, w] : mst[u]) if (v != pu) {
        sptb[0][v] = make_pair(u, make_pair(w, w));
        dep[v] = dep[u] +1;
        dfs(u, v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int V, E; cin >> V >> E;

    struct edge { int id, u, v, w; };
    vector<edge> edges; edges.reserve(E);
    for (int id = 0; id < E; ++id) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({ id, u, v, w });
    }

    auto edges_s = edges;
    sort(edges_s.begin(), edges_s.end(), [] (const edge& e1, const edge& e2) {
        return e1.w < e2.w;
    });
    UnionFind uf(V+1);
    mst.resize(V+1);
    bitset<200'000> used;

    int W = 0;
    for (auto& [id, u, v, w] : edges_s) if (uf.unite(u, v)) {
        mst[u].emplace_back(v, w);
        mst[v].emplace_back(u, w);
        used.set(id);
        W += w;
    }
    if ((int)used.count() < V-1 || E == V-1) {
        cout << -1;
        return 0;
    }

    int logV = 0;
    for (int n = 1; n < V; n <<= 1, ++logV);
    sptb.resize(logV+1, vector<pair<int, ii> >(V+1));
    dep.resize(V+1);

    dfs(0, 1);

    auto greatest_two = [] (const ii& a, const ii& b) {
        set<int> s {a.first, a.second, b.first, b.second};
        int g = *s.rbegin(); s.erase(g);
        if (s.size()) return make_pair(g, *s.rbegin());
        return make_pair(g, g);
    };

    for (int k = 0; k < logV; ++k)
    for (int u = 2; u <= V; ++u) {
        int& v = sptb[k][u].first;
        sptb[k+1][u].first  = sptb[k][v].first;
        sptb[k+1][u].second = greatest_two(sptb[k][u].second, sptb[k][v].second);
    }

    int W2 = INT_MAX;
    for (auto& [id, u, v, w] : edges) if (!used[id]) {
        set<int> s;

        if (dep[u] < dep[v]) swap(u, v);
        for (int t = dep[u] - dep[v], k = 0; t; t >>= 1, ++k) {
            if (t & 1) {
                auto& [m1, m2] = sptb[k][u].second;
                s.emplace(m1); s.emplace(m2);
                u = sptb[k][u].first;
            }
        }
        if (u != v) {
            for (int k = logV; ~k; --k) {
                if (sptb[k][u].first != sptb[k][v].first) {
                    auto& [m1, m2] = sptb[k][u].second;
                    s.emplace(m1); s.emplace(m2);
                    auto& [m3, m4] = sptb[k][v].second;
                    s.emplace(m3); s.emplace(m4);
                    u = sptb[k][u].first;
                    v = sptb[k][v].first;
                }
            }
            auto& [m1, m2] = sptb[0][u].second;
            s.emplace(m1); s.emplace(m2);
            auto& [m3, m4] = sptb[0][v].second;
            s.emplace(m3); s.emplace(m4);
        }

        int g1 = *s.rbegin(); s.erase(g1);
        if (g1 < w) W2 = min(W2, W + w - g1);
        else if (s.size()) {
            int g2 = *s.rbegin();
            if (g2 < w) W2 = min(W2, W + w - g2);
        }
    }

    cout << (W < W2 && W2 != INT_MAX? W2 : -1);
    return 0;
}
