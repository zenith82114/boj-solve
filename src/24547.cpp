/*
 * 24547 - Harmonic lemma + Square root decomposition
 * Date: 2023.5.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

template <typename T>
struct SegTree {
    int N;
    vector<T> ar;
    SegTree(): N(1<<17), ar(1<<18) {}
    void init() {
        for (int i = N-1; i; --i) ar[i] += ar[i<<1] + ar[i<<1|1];
    }
    void add(int i, T x) {
        for (i |= N; i; i >>= 1) ar[i] += x;
    }
    T query(int i, int j) {
        T ans = 0;
        i = max(i, 0);
        j = min(j, N-1);
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans += ar[i++];
            if (~j&1) ans += ar[j--];
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    constexpr int CACHE_SIZE = 320;

    int N; cin >> N;
    vector<int> A(N+1);
    SegTree<i64> segt_sum;
    SegTree<int> segt_cnt;
    vector<int> cache(CACHE_SIZE);

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        segt_sum.ar[1<<17 | A[i]] += A[i];
        segt_cnt.ar[1<<17 | A[i]]++;
        for (int x = 1; x < CACHE_SIZE; ++x) cache[x] += A[i] % x;
    }
    segt_sum.init();
    segt_cnt.init();

    int Q; cin >> Q;
    while (Q--) {
        int op; cin >> op;
        i64 ans = 0;

        if (op == 1) {
            int x; cin >> x;
            if (x < CACHE_SIZE) cout << cache[x] << '\n';
            else {
                for (int j = 0; j * x <= 100000; ++j) {
                    i64 s = segt_sum.query(j * x, (j+1) * x - 1);
                    i64 c = segt_cnt.query(j * x, (j+1) * x - 1);
                    ans += s - c * j * x;
                }
                cout << ans << '\n';
            }
        }
        else if (op == 2) {
            int x; cin >> x;
            const int sqrtx = [] (int x) {
                int l = 1, r = 320;
                while (l < r) {
                    int mid = (l + r)>>1;
                    if (mid * mid < x) l = mid+1; else r = mid;
                }
                return l;
            } (x);

            ans = x < 100000? (i64)x * segt_cnt.query(x+1, 100000) : 0;
            for (int j = 1; j < sqrtx; ++j) {
                i64 s = segt_sum.query(x / (j+1) + 1, x / j);
                i64 c = segt_cnt.query(x / (j+1) + 1, x / j);
                ans += c * x - s * j;
            }
            for (int j = 1; j * sqrtx <= x; ++j) {
                i64 c = segt_cnt.query(j, j);
                ans += c * (x % j);
            }
            cout << ans << '\n';
        }
        else {
            int i, x; cin >> i >> x;
            int oldx = A[i]; A[i] = x;
            segt_sum.add(oldx, -oldx); segt_sum.add(x, x);
            segt_cnt.add(oldx, -1); segt_cnt.add(x, 1);
            for (int y = 1; y < CACHE_SIZE; ++y)
                cache[y] += (x % y) - (oldx % y);
        }
    }

    return 0;
}
