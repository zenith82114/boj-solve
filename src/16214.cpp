/*
 * Q16214 - Euler's totient function
 * Date: 2024.3.23
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int SZ = 32000;
array<int, SZ> spf;
vector<int> primes;

inline int pow_mod(int x, int e, int m) {
    int y = 1;
    for (; e; e >>= 1) {
        if (e&1) y = (1ll*y*x) % m;
        x = (1ll*x*x) % m;
    }
    return y;
}

int phi(int m) {
    int ans = m;
    for (int p : primes) {
        if (m == 1) break;
        if (m%p == 0) {
            ans -= ans/p;
            while (m%p == 0) m /= p;
        }
    }
    if (m > 1) ans -= ans/m;
    return ans;
}

int func(int n, int phi_m) {
    if (phi_m == 1) return 1;

    int r = func(n, phi(phi_m));
    int64_t y = 1ll;
    for (int j = 0; j < r && y < 2*phi_m; ++j) y *= n;
    if (y < 2*phi_m) return y;
    return pow_mod(n, r, phi_m) + phi_m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 2; i < SZ; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.emplace_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1ll*i*p >= (int64_t)SZ) break;
            spf[i*p] = p;
        }
    }

    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        cout << pow_mod(n, func(n, phi(m)), m) << '\n';
    }

    return 0;
}
