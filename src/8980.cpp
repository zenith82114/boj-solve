/*
 * Q8980 - Greedy
 * Date: 2023.9.8
 */

#include<bits/stdc++.h>
using namespace std;

class LazySegTree {
    int N, lgN;
    vector<int> ar, lz;

    void apply(int i, int x) {
        ar[i] += x;
        if (i < N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1, lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    void pull(int i) {
        ar[i] = max(ar[i<<1], ar[i<<1|1]);
    }
public:
    LazySegTree(int sz) {
        N = 1; lgN = 0;
        while (N < sz) N <<= 1, ++lgN;
        ar.resize(N<<1);
        lz.resize(N);
    }
    void add(int i, int j, int x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if     (i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    int query(int i, int j) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        int ans = 0;
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) ans = max(ans, ar[l++]);
            if (~r&1) ans = max(ans, ar[r--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, C; cin >> N >> C;
    LazySegTree segt(N+1);

    int M; cin >> M;
    using iii = tuple<int, int, int>;
    vector<iii> v(M);
    for (auto& [x, y, k] : v) cin >> x >> y >> k;
    sort(v.begin(), v.end(), [] (const iii& a, const iii& b) {
        return get<1>(a) < get<1>(b);
    });

    int ans = 0;
    for (auto [x, y, k] : v) {
        k = min(k, C - segt.query(x, y-1));
        segt.add(x, y-1, k);
        ans += k;
    }
    cout << ans;
    return 0;
}
