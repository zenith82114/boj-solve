/*
 * Q9662 - Bitmask + Floyd's tortoise and hare
 * Date: 2023.6.19
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using u32 = uint32_t;

    int M; cin >> M;
    int K; cin >> K;
    int bw;
    u32 t = 0u;
    while (K--) {
        cin >> bw;
        t |= 1u<<bw;
    }
    bw++;

    auto f = [bw, t] (u32 x) {
        x <<= 1;
        x &= ~(1u<<bw);
        if ((x & t) != t) x |= 1u;
        return x;
    };

    u32 x0 = 0u;
    for (int i = 1; i < bw; ++i) x0 |= 1u<<i;
    x0 = f(x0);

    u32 x = f(x0);
    u32 y = f(x);
    while (x != y) {
        x = f(x);
        y = f(f(y));
    }
    x = x0;
    int q = 0;
    while (x != y) x = f(x), y = f(y), q++;
    int p = 1; x = f(x);
    while (x != y) x = f(x), p++;

    int ans = 0;
    if (M < q) {
        x = x0;
        for (int i = 0; i < M; ++i) {
            if (~x & 1u) ans++;
            x = f(x);
        }
    }
    else {
        M -= q;
        for (int i = q; i < q + p; ++i) {
            if (~x & 1u) ans++;
            x = f(x);
        }
        ans *= (M / p);
        for (int i = q; i < q + (M % p); ++i) {
            if (~x & 1u) ans++;
            x = f(x);
        }
        x = x0;
        for (int i = 0; i < q; ++i) {
            if (~x & 1u) ans++;
            x = f(x);
        }
    }
    cout << ans;
    return 0;
}
