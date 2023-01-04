/*
 * Q13538 - Persistent segment tree
 * Date: 2023.1.4
 */

#include<bits/stdc++.h>
using namespace std;

class PersistentSegTree {
    struct Node {
        int l = -1, r = -1, val = 0;
    };
    vector<int> roots;
    vector<Node> nodes;
    static const int N = 1<<19;

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
    void insert_util(int pn, int n, int s, int e, int x) {
        if (s == e) {
            nodes[n].val = nodes[pn].val + 1;
            return;
        }
        int m = (s + e)>>1;
        if (x <= m) {
            nodes[n].l = nodes.size();
            nodes[n].r = nodes[pn].r;
            nodes.emplace_back();
            insert_util(nodes[pn].l, nodes[n].l, s, m, x);
        }
        else {
            nodes[n].l = nodes[pn].l;
            nodes[n].r = nodes.size();
            nodes.emplace_back();
            insert_util(nodes[pn].r, nodes[n].r, m+1, e, x);
        }
        nodes[n].val = nodes[nodes[n].l].val + nodes[nodes[n].r].val;
    }
    int query_xor_util(int n1, int n2, int s, int e, int b, int x) {
        if (s == e) return s;
        int m = (s + e)>>1;
        if (x & b) {
            if (nodes[nodes[n1].l].val < nodes[nodes[n2].l].val)
                return query_xor_util(nodes[n1].l, nodes[n2].l, s, m, b>>1, x ^ b);
            else
                return query_xor_util(nodes[n1].r, nodes[n2].r, m+1, e, b>>1, x);
        }
        else {
            if (nodes[nodes[n1].r].val < nodes[nodes[n2].r].val)
                return query_xor_util(nodes[n1].r, nodes[n2].r, m+1, e, b>>1, x);
            else
                return query_xor_util(nodes[n1].l, nodes[n2].l, s, m, b>>1, x ^ b);
        }
    }
    int query_leq_util(int n1, int n2, int s, int e, int x) {
        if (s == e) return - nodes[n1].val + nodes[n2].val;
        int m = (s + e)>>1;
        if (x <= m)
            return query_leq_util(nodes[n1].l, nodes[n2].l, s, m, x);
        else
            return query_leq_util(nodes[n1].r, nodes[n2].r, m+1, e, x)
                - nodes[nodes[n1].l].val + nodes[nodes[n2].l].val;
    }
    int query_rank_util(int n1, int n2, int s, int e, int k) {
        if (s == e) return s;
        int m = (s + e)>>1;
        int d = nodes[nodes[n2].l].val - nodes[nodes[n1].l].val;
        if (k <= d)
            return query_rank_util(nodes[n1].l, nodes[n2].l, s, m, k);
        else
            return query_rank_util(nodes[n1].r, nodes[n2].r, m+1, e, k - d);
    }
public:
    PersistentSegTree() {
        roots.emplace_back(0);
        nodes.emplace_back();
        init_util(0, 0, N-1);
    }
    void insert(int x) {
        int pn = roots.back();
        roots.emplace_back(nodes.size());
        nodes.emplace_back();
        insert_util(pn, roots.back(), 0, N-1, x);
    }
    int query_xor(int i, int j, int x) {
        return query_xor_util(roots[i-1], roots[j], 0, N-1, N>>1, x);
    }
    void pop_back(int k) {
        roots.resize(roots.size() - k);
    }
    int query_leq(int i, int j, int x) {
        return query_leq_util(roots[i-1], roots[j], 0, N-1, x);
    }
    int query_rank(int i, int j, int k) {
        return query_rank_util(roots[i-1], roots[j], 0, N-1, k);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    PersistentSegTree psegt;

    int M; cin >> M;
    while (M--) {
        int q; cin >> q;
        int i, j, k, x;
        switch (q) {
        case 1:
            cin >> x;
            psegt.insert(x);
            break;
        case 2:
            cin >> i >> j >> x;
            cout << psegt.query_xor(i, j, x) << '\n';
            break;
        case 3:
            cin >> k;
            psegt.pop_back(k);
            break;
        case 4:
            cin >> i >> j >> x;
            cout << psegt.query_leq(i, j, x) << '\n';
            break;
        case 5:
            cin >> i >> j >> k;
            cout << psegt.query_rank(i, j, k) << '\n';
            break;
        default: break;
        }
    }

    return 0;
}
