/*
 * Q2336 - Bottom-up segment tree
 * Date: 2022.5.24
 */

#include<bits/stdc++.h>
using namespace std;

class SegTree {
    int N_;
    vector<int> A_;
    int ceil_pow2(int n) {
        if (n & (n-1)) {
            for (int i = 1; i < 32; i <<= 1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }
public:
    SegTree(int N) {
        N_ = ceil_pow2(N);
        A_.resize(N_<<1, INT_MAX);
    }
    void insert(int x, int i) {
        i += N_;
        for (A_[i] = x; i > 1; i >>= 1)
            A_[i >> 1] = min(A_[i], A_[i^1]);
    }
    int query(int i, int j) {
        int ret = INT_MAX;
        for (i += N_, j += N_; i <= j; i >>= 1, j >>= 1) {
            if (i & 1)
                ret = min(ret, A_[i++]);
            if (!(j & 1))
                ret = min(ret, A_[j--]);
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<int> stor1, stor2;
    int N, s;

    cin >> N;
    stor1.resize(N+1);
    for (int i = 0; i < N; ++i) {
        cin >> s;
        stor1[s] = i;
    }
    stor2.resize(N+1);
    for (int i = 0; i < N; ++i) {
        cin >> s;
        stor2[s] = i;
    }

    SegTree segt(N);
    int cnt = 0;
    while (N--) {
        cin >> s;
        segt.insert(stor1[s], stor2[s]);
        cnt += (segt.query(0, stor2[s]) == stor1[s]);
    }
    cout << cnt << '\n';

    return 0;
}
