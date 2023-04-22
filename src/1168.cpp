/*
 * Q1168 - Josephus sequence using segment tree
 * Date: 2021.8.29
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int N;
    vector<int> A;
    constexpr int lc(int n) { return n << 1; }
    constexpr int rc(int n) { return (n << 1) | 1; }
    void init(int n, int i, int j) {
        if (i == j) A[n] = 1;
        else {
            int m = (i + j) / 2;
            init(lc(n), i, m);
            init(rc(n), m + 1, j);
            A[n] = A[lc(n)] + A[rc(n)];
        }
    }
    int query_util(int n, int l, int r, int i) {
        A[n]--;
        if (l == r) return l;
        int m = (l + r) / 2;
        return i > A[lc(n)]
            ? query_util(rc(n), m + 1, r, i - A[lc(n)])
            : query_util(lc(n), l, m, i);
    }
public:
    seg_tree(int n) {
        N = n;
        int sz = 1;
        while (sz < n) sz <<= 1;
        A.resize(sz<<1);
        init(1, 1, N);
    }
    int query(int i) {
        return query_util(1, 1, N, i);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, K; cin >> N >> K;
    seg_tree segt(N);

    int i = K;
    cout << '<' << segt.query(K);
    while (--N) {
        i += (K - 1);
        i = ((i - 1) % N) + 1;
        cout << ", " << segt.query(i);
    }
    cout << ">\n";

    return 0;
}
