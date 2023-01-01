/*
 * Q10999a - Iterative lazy segment tree
 * Date: 2023.1.1
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;

class LazySegTree {
    int N, lgN;
    vector<i64> ar, lz;
    int floor_log2(int i) {
        int m = 0;
        for (int k = lgN; k; k >>= 1)
            while (m+k <= lgN && 1<<(m+k) <= i) m += k;
        return m;
    }
    void apply(int i, i64 x) {
        ar[i] += x * (N >> floor_log2(i));
        if (i < N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1, lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0ll;
    }
    void pull(int i) {
        ar[i] = ar[i<<1] + ar[i<<1|1];
    }
public:
    LazySegTree(const vector<i64>& data) {
        int M = data.size();
        N = 1; lgN = 0;
        while (N < M) { N <<= 1; lgN++; }
        ar.resize(N<<1, 0ll);
        lz.resize(N, 0ll);

        copy(data.begin(), data.end(), ar.begin() + N);
        for (int i = N-1; i; --i)
            ar[i] = ar[i<<1] + ar[i<<1|1];
    }
    void add(int i, int j, i64 x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (i>>k<<k != i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if (l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if (i>>k<<k != i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    i64 query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (i>>k<<k != i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        i64 ans = 0ll;
        for (; i <= j; i >>= 1, j >>= 1) {
            if (i&1) ans += ar[i++];
            if (~j&1) ans += ar[j--];
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;
    vector<i64> A(N);
    for (i64& a : A) cin >> a;

    LazySegTree segt(A);
    M += K;
    while (M--) {
        int q, i, j; cin >> q >> i >> j; i--; j--;
        if (q&1) {
            i64 x; cin >> x;
            segt.add(i, j, x);
        }
        else
            cout << segt.query(i, j) << '\n';
    }

    return 0;
}
