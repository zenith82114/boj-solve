/*
 * Q10999 - Lazy propagation in segment tree
 * Date: 2022.2.10
 */

#include<bits/stdc++.h>
using namespace std;
using llint = long long;

class SegTree {
    int N;
    vector<llint> A, lazy;
    constexpr int ceilPow2(int n) {
        if (n & (n-1)) {
            for (int i=1; i<32; i<<=1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }
    int lChld(int n) { return n<<1; }
    int rChld(int n) { return n<<1 | 1; }
    void initUtil(int n, int l, int r, vector<llint>& v) {
        int m = (l+r)/2;
        if (l != r) {
            initUtil(lChld(n), l, m, v);
            initUtil(rChld(n), m+1, r, v);
            A[n] = A[lChld(n)] + A[rChld(n)];
        }
        else A[n] = v[l];
    }
    void addUtil(int n, int l, int r, int i, int j, llint x) {
        int m = (l+r)/2;
        if (lazy[n]) {
            A[n] += (r-l+1)*lazy[n];
            if (l != r) {
                lazy[lChld(n)] += lazy[n];
                lazy[rChld(n)] += lazy[n];
            }
            lazy[n] = 0;
        }
        if (l > j || r < i)
            return;
        if (l < i || r > j) {
            addUtil(lChld(n), l, m, i, j, x);
            addUtil(rChld(n), m+1, r, i, j, x);
            A[n] = A[lChld(n)] + A[rChld(n)];
        }
        else {
            A[n] += (r-l+1)*x;
            if (l != r) {
                lazy[lChld(n)] += x;
                lazy[rChld(n)] += x;
            }
        }
    }
    llint queryUtil(int n, int l, int r, int i, int j) {
        int m = (l+r)/2;
        if (lazy[n]) {
            A[n] += (r-l+1)*lazy[n];
            if (l != r) {
                lazy[lChld(n)] += lazy[n];
                lazy[rChld(n)] += lazy[n];
            }
            lazy[n] = 0;
        }
        if (l > j || r < i)
            return 0;
        if (l < i || r > j)
            return queryUtil(lChld(n), l, m, i, j)
            + queryUtil(rChld(n), m+1, r, i, j);
        return A[n];
    }
public:
    void init(vector<llint>& v) {
        N = v.size();
        A.assign(ceilPow2(N)<<1, 0);
        lazy.assign(A.size(), 0);
        initUtil(1, 0, N-1, v);
    }
    void add(int i, int j, llint x) {
        addUtil(1, 0, N-1, i, j, x);
    }
    llint query(int i, int j) {
        return queryUtil(1, 0, N-1, i, j);
    }
} segt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<llint> v;
    int N, M, K, q, i, j, x;

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
