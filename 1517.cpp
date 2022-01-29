/*
 * Q1517 - Inversion counting using segment tree
 * Date: 2021.8.31
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int, int> pii;

// least power of 2 not smaller than n
constexpr int ceil_pow2(int n) {
    if (n & (n - 1)) {
        for (int i = 1; i < 32; i <<= 1)
            n |= (n >> i);
        return n + 1;
    }
    // n is a power of 2
    return n;
}

// counting segment tree (stores # of elements in interval)
class SegTree {
    int N;
    vector<int> A;
    constexpr int lChild(int n) { return n << 1; }
    constexpr int rChild(int n) { return n << 1 | 1; }
    // return sum of {A[l]...A[r]}
    int queryUtil(int n, int nl, int nr, int l, int r) {
        if (nl == l && nr == r) return A[n];
        int nm = (nl + nr) / 2;
        if (nm >= r) return queryUtil(lChild(n), nl, nm, l, r);
        if (nm < l)  return queryUtil(rChild(n), nm + 1, nr, l, r);
        return queryUtil(lChild(n), nl, nm, l, nm)
             + queryUtil(rChild(n), nm + 1, nr, nm + 1, r);
    }
public:
    SegTree(int size) {
        N = size;
        A.resize(ceil_pow2(size)<<1);
    }
    void insert(int x) {
        int n = 1, l = 1, r = N;
        while (l < r) {
            A[n]++;
            int m = (l + r) / 2;
            if (x > m) {
                l = m + 1;
                n = rChild(n);
            } else {
                r = m;
                n = lChild(n);
            }
        }
        A[n]++;
    }
    int query(int x) {
        if (x == N) return 0;
        return queryUtil(1, 1, N, x + 1, N);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N;
    int64_t S = 0;

    cin >> N;
    vector<pii> v(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i].first;
        v[i].second = i + 1;
    }
    sort(v.begin(), v.end());

    SegTree segt(N);
    for (pii& p : v) {
        S += segt.query(p.second);
        segt.insert(p.second);
    }

    cout << S << '\n';
    return 0;
}
