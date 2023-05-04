/*
 * Q14898 - Persistent segment tree
 * Date: 2023.5.4
 */

#include<bits/stdc++.h>
using namespace std;

class PersistentSegTree {
    struct Node { int l = -1, r = -1, val = 0; };
    vector<int> roots;
    vector<Node> nodes;
    int N;
    int pr;

    void add_util(int pn, int n, int s, int e, int i, int x) {
        if (s == e) {
            nodes[n].val = (pn != -1? nodes[pn].val : 0) + x;
            return;
        }
        int m = (s + e)>>1;
        if (i <= m) {
            nodes[n].l = nodes.size();
            nodes[n].r = pn != -1? nodes[pn].r : -1;
            nodes.emplace_back();
            add_util(pn != -1? nodes[pn].l : -1, nodes[n].l, s, m, i, x);
        }
        else {
            nodes[n].l = pn != -1? nodes[pn].l : -1;
            nodes[n].r = nodes.size();
            nodes.emplace_back();
            add_util(pn != -1? nodes[pn].r : -1, nodes[n].r, m+1, e, i, x);
        }
        auto& [l, r, v] = nodes[n];
        if (l != -1) v += nodes[l].val;
        if (r != -1) v += nodes[r].val;
    }
    int query_util(int n, int s, int e, int i, int j) {
        if (n == -1) return 0;
        int m = (s + e)>>1;
        if (s > j || e < i) return 0;
        if (s < i || e > j) return
            query_util(nodes[n].l, s, m, i, j) +
            query_util(nodes[n].r, m+1, e, i, j);
        return nodes[n].val;
    }
public:
    PersistentSegTree(int N): N(N), pr(0) {
        // avoid MLE
        roots.reserve(1<<20); roots.emplace_back(0);
        nodes.reserve(20<<20); nodes.emplace_back();
    }
    void add(int i, int x, bool commit) {
        int r = nodes.size();
        nodes.emplace_back();
        add_util(pr, r, 1, N, i, x);
        pr = r;
        if (commit) roots.emplace_back(pr);
    }
    int query(int i, int j) {
        return query_util(roots[j], 1, N, i, j);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    auto sA(A); sort(sA.begin(), sA.end());
    vector<int> last(N);
    PersistentSegTree pst(N);

    for (int i = 0; i < N; ++i) {
        int b = lower_bound(sA.begin(), sA.end(), A[i]) - sA.begin();
        if (last[b]) pst.add(last[b], -1, false);
        pst.add(i+1, 1, true);
        last[b] = i+1;
    }

    int Q; cin >> Q;
    int q = 0;
    while (Q--) {
        int x, r; cin >> x >> r;
        q = pst.query(x + q, r);
        cout << q << '\n';
    }

    return 0;
}
