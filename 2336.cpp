/*
 * Q2336 - Bottom-up segment tree
 * Date: 2022.5.24
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int N;
    vector<int> A;
public:
    seg_tree(int sz) {
        N = 1;
        while (N < sz) N <<= 1;
        A.resize(N<<1, INT_MAX);
    }
    void insert(int x, int i) {
        i += N;
        for (A[i] = x; i > 1; i >>= 1)
            A[i >> 1] = min(A[i], A[i^1]);
    }
    int query(int i, int j) {
        int ret = INT_MAX;
        for (i += N, j += N; i <= j; i >>= 1, j >>= 1) {
            if (i & 1)
                ret = min(ret, A[i++]);
            if (!(j & 1))
                ret = min(ret, A[j--]);
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> stor1(N+1);
    for (int i = 0; i < N; ++i) {
        int s; cin >> s;
        stor1[s] = i;
    }
    vector<int> stor2(N+1);
    for (int i = 0; i < N; ++i) {
        int s; cin >> s;
        stor2[s] = i;
    }

    seg_tree segt(N);
    int cnt = 0;
    while (N--) {
        int s; cin >> s;
        segt.insert(stor1[s], stor2[s]);
        cnt += (segt.query(0, stor2[s]) == stor1[s]);
    }

    cout << cnt << '\n';
    return 0;
}
