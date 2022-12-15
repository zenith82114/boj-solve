/*
 * Q10999 - Lazy propagation in segment tree
 * Date: 2022.2.10
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class seg_tree {
    int N;
    vector<ll> A, lazy;

    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1 | 1; }
    void init_util(int n, int l, int r, vector<ll>& v) {
        int m = (l+r)/2;
        if (l != r) {
            init_util(lc(n), l, m, v);
            init_util(rc(n), m+1, r, v);
            A[n] = A[lc(n)] + A[rc(n)];
        }
        else A[n] = v[l];
    }
    void add_util(int n, int l, int r, int i, int j, ll x) {
        int m = (l+r)/2;
        if (lazy[n]) {
            A[n] += (r-l+1)*lazy[n];
            if (l != r) {
                lazy[lc(n)] += lazy[n];
                lazy[rc(n)] += lazy[n];
            }
            lazy[n] = 0;
        }
        if (l > j || r < i)
            return;
        if (l < i || r > j) {
            add_util(lc(n), l, m, i, j, x);
            add_util(rc(n), m+1, r, i, j, x);
            A[n] = A[lc(n)] + A[rc(n)];
        }
        else {
            A[n] += (r-l+1)*x;
            if (l != r) {
                lazy[lc(n)] += x;
                lazy[rc(n)] += x;
            }
        }
    }
    ll query_util(int n, int l, int r, int i, int j) {
        int m = (l+r)/2;
        if (lazy[n]) {
            A[n] += (r-l+1)*lazy[n];
            if (l != r) {
                lazy[lc(n)] += lazy[n];
                lazy[rc(n)] += lazy[n];
            }
            lazy[n] = 0;
        }
        if (l > j || r < i)
            return 0;
        if (l < i || r > j)
            return query_util(lc(n), l, m, i, j)
                + query_util(rc(n), m+1, r, i, j);
        return A[n];
    }
public:
    void init(vector<ll>& v) {
        N = v.size();
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.assign(sz<<1, 0);
        lazy.assign(A.size(), 0);
        init_util(1, 0, N-1, v);
    }
    void add(int i, int j, ll x) {
        add_util(1, 0, N-1, i, j, x);
    }
    ll query(int i, int j) {
        return query_util(1, 0, N-1, i, j);
    }
} segt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;
    vector<ll> v(N+1);
    for (int i = 1; i <= N; cin >> v[i++]);
    segt.init(v);

    M += K;
    while (M--) {
        int q; cin >> q;
        int i, j, x;
        if (q&1) {
            cin >> i >> j >> x;
            segt.add(i, j, x);
        }
        else {
            cin >> i >> j;
            cout << segt.query(i, j) << '\n';
        }
    }

    return 0;
}
