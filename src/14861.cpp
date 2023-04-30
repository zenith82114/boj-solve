/*
 * Q14861 - Mobius Inversion + Inclusion/Exclusion
 * Date: 2023.4.30
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    constexpr int LIMIT = 4'000'000;
    vector<int> spf(LIMIT + 1), primes;
    vector<int> mu(LIMIT + 1); mu[1] = 1;
    vector<uint> F(LIMIT + 1); F[1] = 1;

    for (int i = 2; i <= LIMIT; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            mu[i] = -1;
            F[i] = i * (1 - i);
            primes.emplace_back(i);
        }
        for (int p : primes) {
            if (p < spf[i] && 1ll * i * p <= LIMIT) {
                spf[i * p] = p;
                mu[i * p] = mu[i] * mu[p];
                F[i * p] = F[i] * F[p];
            }
            else break;
        }
        if (1ll * i * spf[i] <= LIMIT) {
            spf[i * spf[i]] = spf[i];
            F[i * spf[i]] = F[i] * spf[i];
        }
    }
    partial_sum(F.begin(), F.end(), F.begin());

    auto calc = [&] (uint N, uint M) {
        uint ret = 0;
        for (uint i = 1, j = 0; i <= min(N, M); i = j+1) {
            j = min(N / (N / i), M / (M / i));
            uint s = N / i, t = M / i;
            ret += (s * (s+1) / 2) * (t * (t+1) / 2) * (F[j] - F[i-1]);
        }
        return ret;
    };

    int TC; cin >> TC;
    while (TC--) {
        uint N, M; cin >> N >> M;
        uint ans = 0;
        for (uint k = 1; k*k <= min(N, M); ++k)
            ans += mu[k] * k*k * calc(N / (k*k), M / (k*k));
        cout << (ans & ((1<<30) - 1)) << '\n';
    }

    return 0;
}
