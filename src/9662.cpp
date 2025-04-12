/*
 * Q9662 - bitmask, Floyd's tortoise and hare
 * Date: 2025.4.12
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
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

    u32 x = f(x0);
    u32 y = f(f(x0));
    while (x != y) x = f(x), y = f(f(y));
    x = x0;
    int q = 0;
    while (x != y) x = f(x), y = f(y), q++;
    int p = 1; x = f(x);
    while (x != y) x = f(x), p++;

    int ans = 0;
    if (M < q) {
        x = x0;
        for (int i = 0; i < M; ++i) {
            x = f(x);
            if (~x & 1u) ans++;
        }
    }
    else {
        M -= q;
        for (int i = q; i < q + p; ++i) {
            x = f(x);
            if (~x & 1u) ans++;
        }
        ans *= (M / p);
        for (int i = q; i < q + (M % p); ++i) {
            x = f(x);
            if (~x & 1u) ans++;
        }
        x = x0;
        for (int i = 0; i < q; ++i) {
            x = f(x);
            if (~x & 1u) ans++;
        }
    }
    cout << ans;
    return 0;
}
