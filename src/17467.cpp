/*
 * Q17467 - Barrett reduction
 * Date: 2023.5.16
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    i64 N, P; cin >> N >> P;

    int l = 1, r = 30;
    while (l != r) {
        int m = (l + r)>>1;
        if (1LL<<m < P) l = m+1; else r = m;
    }
    const int k = l;
    const int k1 = k - 1, k2 = k + 1;
    const int m = (int)((1LL<<(k<<1)) / P);

    auto mult = [&] (i64& x, i64 y) {
        x *= y;
        int q = ((x >> k1) * m) >> k2;
        x -= q * P;
        x = x < P? x : x - P;
        x = x < P? x : x - P;
    };

    i64 x0 = 1LL, x1 = 1LL, x2 = 1LL, x3 = 1LL;
    if (N < P>>1) {
        int i = 2;
        for (; i < 4 && i <= N; ++i) mult(x0, i);
        for (; (i|3) <= N; i += 4) {
            mult(x0, i); mult(x1, i|1); mult(x2, i|2); mult(x3, i|3);
        }
        mult(x0, x1); mult(x0, x2); mult(x0, x3);
        for (; i <= N; ++i) mult(x0, i);
        cout << x0;
    } else {
        int i = N+1;
        for (; (i&3) != 0 && i < P; ++i) mult(x0, i);
        for (; (i|3) < P; i += 4) {
            mult(x0, i); mult(x1, i|1); mult(x2, i|2); mult(x3, i|3);
        }
        mult(x0, x1); mult(x0, x2); mult(x0, x3);
        for (; i < P; ++i) mult(x0, i);

        i64 y = 1LL;
        for (int e = P-2; e; e >>= 1) {
            if (e&1) mult(y, x0);
            mult(x0, x0);
        }
        cout << P - y;
    }

    return 0;
}
