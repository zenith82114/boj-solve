/*
 * Q11897 - Disjoint sets
 * Date: 2024.6.24
 */

#include<bits/stdc++.h>
using namespace std;

struct DisjointSets {
    vector<int> a;
    int n;

    DisjointSets(int n): a(n, -1), n(n-1) {}
    int find(int i) {
        if (a[i] < 0) return i;
        return a[i] = find(a[i]);
    }
    void clear() {
        fill(a.begin(), a.end(), -1);
        n = a.size()-1;
    }
    bool unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return false;
        if (a[i] == a[j]) --a[i];
        if (a[i] > a[j]) swap(i, j);
        a[j] = i;
        --n;
        return true;
    }
};

array<pair<int, int>, 123460> edg;
array<int, 705> pl, pr;
array<int, 123460> ipl, ipr;
array<array<int, 705>, 705> mem;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int V, E; cin >> V >> E;
    for (int i = 1; i <= E; ++i) {
        auto& [x, y] = edg[i]; cin >> x >> y;
    }

    DisjointSets dsu(V+1);
    int U = 0;
    ipl[0] = 0;
    for (int i = 1; i <= E; ++i) {
        ipl[i] = ipl[i-1];
        if (dsu.unite(edg[i].first, edg[i].second)) {
            ++ipl[i];
            pl[++U] = i;
        }
    }
    dsu.clear();
    U = 0;
    ipr[E+1] = 0;
    for (int i = E; i > 0; --i) {
        ipr[i] = ipr[i+1];
        if (dsu.unite(edg[i].first, edg[i].second)) {
            ++ipr[i];
            pr[++U] = i;
        }
    }

    for (int i = 0; i <= U; ++i) {
        dsu.clear();
        for (int j = 1; j <= i; ++j) {
            dsu.unite(edg[pl[j]].first, edg[pl[j]].second);
        }
        mem[i][0] = dsu.n;
        for (int j = 1; j <= U; ++j) {
            dsu.unite(edg[pr[j]].first, edg[pr[j]].second);
            mem[i][j] = dsu.n;
        }
    }

    int Q; cin >> Q;
    while (Q--) {
        int a, b; cin >> a >> b;
        cout << mem[ipl[a-1]][ipr[b+1]] << '\n';
    }

    return 0;
}
