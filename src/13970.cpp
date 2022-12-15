/*
 * Q13970 - Euler's totient function
 * Date: 2022.12.15
 */

#include<bits/stdc++.h>
using namespace std;

inline int pow_mod(int x, int e, int m) {
    int y = 1;
    for (; e; e >>= 1) {
        if (e&1) y = (1ll * y * x) % m;
        x = (1ll * x * x) % m;
    }
    return y;
}

vector<int> phi, X;
int N;

int func(int i, int phi_m) {
    if (phi_m == 1 || i == N) return 1;

    int r = func(i+1, phi[phi_m]);
    int64_t y = 1ll;
    for (int j = 0; j < r && y < 2*phi_m; ++j)
        y *= X[i];
    if (y < 2*phi_m) return y;
    return pow_mod(X[i], r, phi_m) + phi_m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T, M; cin >> T >> M;

    phi.resize(M+1);
    iota(phi.begin(), phi.end(), 0);
    for (int p = 2; p <= M; ++p) if (phi[p] == p) {
        for (int q = p; q <= M; q += p) {
            phi[q] -= phi[q] / p;
        }
    }

    while (T--) {
        cin >> N;
        X.resize(N);
        for (int& x : X) cin >> x;
        cout << pow_mod(X[0], func(1, phi[M]), M) << '\n';
    }

    return 0;
}
