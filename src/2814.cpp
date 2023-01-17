/*
 * Q2814 - Inclusion & Exclusion + Binary search
 * Date: 2023.1.17
 *
 * Warning: slow code (~800ms)
 */

#include<bits/stdc++.h>
using namespace std;

int solve(int M, int P, const vector<int>& primes) {
    int64_t ans = M;
    auto v = primes;
    int sgn = -1;

    while (!v.empty()) {
        for (int& a : v) ans += sgn * (M / a);
        sgn = -sgn;

        vector<int> nv;
        for (int& a : v) {
            for (const int& p : primes) {
                if ((int64_t)a * p > M) break;
                if (a % p) nv.emplace_back(a * p);
            }
        }

        sort(nv.begin(), nv.end());
        nv.erase(unique(nv.begin(), nv.end()), nv.end());
        v.swap(nv);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    constexpr int _1e9 = 1'000'000'000;
    int N, P; cin >> N >> P;

    if (N == 1) {
        cout << P; return 0;
    }
    if ((int64_t)_1e9 < (int64_t)P * P) {
        cout << 0; return 0;
    }

    vector<int> primes;
    bitset<32'000> is_prime; is_prime.set();
    for (int i = 2; i < P; ++i) if (is_prime[i]) {
        primes.emplace_back(i);
        for (int j = i * i; j < P; j += i) is_prime.reset(j);
    }

    int M = P - 1;
    int M_end = (_1e9 / P) + 1;
    for (int k = M_end - M; k; k /= 2)
        while (M + k <= M_end && solve(M + k, P, primes) < N)
            M += k;

    int ans = (M + 1) * P;
    cout << (ans > _1e9? 0 : ans);
    return 0;
}
