/*
 * Q1517 - Inversion counting using segment tree
 * Date: 2021.8.31
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int N;
    vector<int> A;
    constexpr int lc(int n) { return n << 1; }
    constexpr int rc(int n) { return n << 1 | 1; }
    int query_util(int n, int nl, int nr, int l, int r) {
        if (nl == l && nr == r) return A[n];
        int nm = (nl + nr) / 2;
        if (nm >= r) return query_util(lc(n), nl, nm, l, r);
        if (nm < l)  return query_util(rc(n), nm +1, nr, l, r);
        return query_util(lc(n), nl, nm, l, nm)
             + query_util(rc(n), nm +1, nr, nm +1, r);
    }
public:
    seg_tree(int n) {
        N = n;
        int sz = 1;
        while (sz < n) sz <<= 1;
        A.resize(sz << 1);
    }
    void insert(int x) {
        int n = 1, l = 1, r = N;
        while (l < r) {
            A[n]++;
            int m = (l + r) / 2;
            if (x > m) {
                l = m +1;
                n = rc(n);
            } else {
                r = m;
                n = lc(n);
            }
        }
        A[n]++;
    }
    int query(int x) {
        if (x == N) return 0;
        return query_util(1, 1, N, x +1, N);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<pair<int, int>> v(N);
    for (int i = 0; i < N; ++i) {
        cin >> v[i].first;
        v[i].second = i + 1;
    }
    sort(v.begin(), v.end());

    seg_tree segt(N);
    int64_t S = 0;
    for (const auto& p : v) {
        S += segt.query(p.second);
        segt.insert(p.second);
    }

    cout << S << '\n';
    return 0;
}
