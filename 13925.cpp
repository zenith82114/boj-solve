/*
 * Q13925 - Lazy propagation of generalized queries
 * Date: 2022.7.2
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class seg_tree {
    struct lazy_struct {
        bool flag = false;
        int m = 0, a = 0;
    };
    const int MOD = (int)1e9 + 7;

    int N;
    vector<int> tree;
    vector<lazy_struct> lazy;

    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1 | 1; }
    int add_mod(int a, int b) { return (a + b) % MOD; }
    int mul_mod(int a, int b) { return (int)((1ll * a * b) % MOD); }
    void lazy_prop(int n, int m, int a) {
        auto& lz = lazy[n];
        if (lz.flag) {
            lz.m = mul_mod(m, lz.m);
            lz.a = add_mod(mul_mod(m, lz.a), a);
        }
        else {
            lz.flag = true;
            lz.m = m, lz.a = a;
        }
    }

    void init_util(int n, int s, int e, vector<int>& A) {
        if (s != e) {
            int mid = (s+e)>>1;
            init_util(lc(n), s, mid, A);
            init_util(rc(n), mid+1, e, A);
            tree[n] = add_mod(tree[lc(n)], tree[rc(n)]);
        }
        else tree[n] = A[s];
    }
    void update_util(int n, int s, int e, int i, int j, int m, int a) {
        auto& lz = lazy[n];
        if (lz.flag) {
            tree[n] = mul_mod(tree[n], lz.m);
            tree[n] = add_mod(tree[n], mul_mod(e-s+1, lz.a));
            if (s != e) {
                lazy_prop(lc(n), lz.m, lz.a);
                lazy_prop(rc(n), lz.m, lz.a);
            }
            lz.flag = false;
        }
        if (s > j || e < i)
            return;
        if (s < i || e > j) {
            int mid = (s+e)>>1;
            update_util(lc(n), s, mid, i, j, m, a);
            update_util(rc(n), mid+1, e, i, j, m, a);
            tree[n] = add_mod(tree[lc(n)], tree[rc(n)]);
        }
        else {
            tree[n] = mul_mod(tree[n], m);
            tree[n] = add_mod(tree[n], mul_mod(e-s+1, a));
            if (s != e) {
                lazy_prop(lc(n), m, a);
                lazy_prop(rc(n), m, a);
            }
        }
    }
    int query_util(int n, int s, int e, int i, int j) {
        auto& lz = lazy[n];
        if (lz.flag) {
            tree[n] = mul_mod(tree[n], lz.m);
            tree[n] = add_mod(tree[n], mul_mod(e-s+1, lz.a));
            if (s != e) {
                lazy_prop(lc(n), lz.m, lz.a);
                lazy_prop(rc(n), lz.m, lz.a);
            }
            lz.flag = false;
        }
        if (s > j || e < i)
            return 0;
        if (s < i || e > j) {
            int mid = (s+e)>>1;
            return add_mod(
                query_util(lc(n), s, mid, i, j),
                query_util(rc(n), mid+1, e, i, j));
        }
        return tree[n];
    }
public:
    seg_tree(vector<int>& A) {
        N = A.size()-1;
        int sz = 1;
        while (sz < N) sz <<= 1;
        tree.resize(sz<<1);
        lazy.resize(tree.size());
        init_util(1, 1, N, A);
    }
    void update(int i, int j, int m, int a) {
        update_util(1, 1, N, i, j, m, a);
    }
    int query(int i, int j) {
        return query_util(1, 1, N, i, j);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N+1);
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    seg_tree segt(A);

    int M; cin >> M;
    while (M--) {
        int q, i, j, v;
        cin >> q >> i >> j;
        switch (q) {
            case 1:
                cin >> v;
                segt.update(i, j, 1, v);
                break;
            case 2:
                cin >> v;
                segt.update(i, j, v, 0);
                break;
            case 3:
                cin >> v;
                segt.update(i, j, 0, v);
                break;
            case 4:
                cout << segt.query(i, j) << '\n';
        }
    }

    return 0;
}
