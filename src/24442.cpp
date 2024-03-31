/*
 * Q24442 - Aliens trick + lazy segment tree
 * Date: 2024.3.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

class LazySegTree {
    int N, lgN;
    vector<pair<i64, int> > ar;
    vector<i64> lz;
    void apply(int i, i64 x) {
        ar[i].first += x;
        if (~i & N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1,   lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    void pull(int i) {
        ar[i] = max(ar[i<<1], ar[i<<1|1]);
    }
public:
    LazySegTree(int sz) {
        for (N = 1, lgN = 0; N < sz; N <<= 1, ++lgN);
        ar.resize(N<<1);
        lz.resize(N);
        for (int i = 0; i < N; ++i) ar[N|i].second = i;
    }
    void add(int i, int j, i64 x) {
        i |= N; j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if (    i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    pair<i64, int> query(int i, int j) {
        i |= N; j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        pair<i64, int> ans(-1, 0);
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans = max(ans, ar[l++]);
            if (~r&1) ans = max(ans, ar[r--]);
        }
        return ans;
    }
};

pair<i64, int> solve(const vector<int>& pre, i64 cost) {
    int n = pre.size() - 1;
    LazySegTree segt(n+1);
    vector<int> cnt(n+1);
    i64 val = 0;

    for (int j = 1; j <= n; ++j) {
        segt.add(pre[j], j-1, 2);
        auto [fi, i] = segt.query(0, j-1);
        cnt[j] = cnt[i] + 1;
        val = fi - cost;
        segt.add(j, j, val);
    }
    return make_pair(val, cnt[n]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    vector<int> pre(n+1), mem(n+1);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        pre[i] = mem[x];
        mem[x] = i;
    }

    i64 lo = 0, hi = 200005;
    while (lo < hi) {
        i64 mid = (lo+hi)>>1;
        int cnt = solve(pre, 2*mid+1).second;
        if (cnt <= k) hi = mid; else lo = mid+1;
    }
    auto [val, cnt] = solve(pre, 2*lo);
    cout << (val/2 + lo*k);
    return 0;
}
