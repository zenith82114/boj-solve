/*
 * Q10999 - Lazy propagation in segment tree
 * Date: 2022.2.10
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

class SegTree {
    int N;
    vector<ll> A, lazy;
    constexpr int ceilPow2(int n) {
        if (n & (n-1)) {
            for (int i=1; i<32; i<<=1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }
    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1 | 1; }
    void initUtil(int n, int l, int r, vector<ll>& v) {
        int m = (l+r)/2;
        if (l != r) {
            initUtil(lc(n), l, m, v);
            initUtil(rc(n), m+1, r, v);
            A[n] = A[lc(n)] + A[rc(n)];
        }
        else A[n] = v[l];
    }
    void addUtil(int n, int l, int r, int i, int j, ll x) {
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
            addUtil(lc(n), l, m, i, j, x);
            addUtil(rc(n), m+1, r, i, j, x);
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
    ll queryUtil(int n, int l, int r, int i, int j) {
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
            return queryUtil(lc(n), l, m, i, j)
            + queryUtil(rc(n), m+1, r, i, j);
        return A[n];
    }
public:
    void init(vector<ll>& v) {
        N = v.size();
        A.assign(ceilPow2(N)<<1, 0);
        lazy.assign(A.size(), 0);
        initUtil(1, 0, N-1, v);
    }
    void add(int i, int j, ll x) {
        addUtil(1, 0, N-1, i, j, x);
    }
    ll query(int i, int j) {
        return queryUtil(1, 0, N-1, i, j);
    }
} segt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<ll> v;
    int N, M, K, q, i, j;
    ll x;

    cin >> N >> M >> K;
    v.resize(N+1);
    for (i=1; i<=N; i++)
        cin >> v[i];
    segt.init(v);

    M += K;
    while (M--) {
        cin >> q;
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
