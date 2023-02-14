/*
 * Q11691 - Mobius Inversion
 * Date: 2023.2.14
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'007;

struct mint {
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        int v; cin >> v; x = mint(v); return is;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(-val); }
    mint pow(int e) const {
        mint y(1), x(*this);
        for (; e; e >>= 1) { if (e&1) { y *= x; } x *= x; }
        return y;
    }
    mint inv() const { return pow(MOD - 2); }

    bool operator==(const mint& x) const { return val == x.val; }
    bool operator!=(const mint& x) const { return val != x.val; }
    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator-(const mint& x) const { return mint(*this) -= x; }
    mint& operator-=(const mint& x) {
        if ((val -= x.val) < 0) val += MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

constexpr int SZ = 1e6 +1;

array<mint, SZ> F;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    array<int, SZ> spf; spf.fill(0);
    vector<int> primes;
    F.fill(0); F[1] = 1;

    int N; cin >> N;
    for (int i = 2; i <= N; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            F[i] = (mint)i * (mint)(1 - i);
            primes.emplace_back(i);
        }
        for (const int& p : primes) {
            if (p < spf[i] && 1ll * i * p <= N) {
                spf[i * p] = p;
                F[i * p] = F[i] * F[p];
            }
            else break;
        }
        if (1ll * i * spf[i] <= N) {
            spf[i * spf[i]] = spf[i];
            F[i * spf[i]] = F[i] * (mint)spf[i];
        }
    }

    for (int i = 1; i < N; ++i) F[i+1] += F[i];

    mint ans(0);
    for (int i = 1, j = 0; i <= N; i = j+1) {
        j = N / (N / i);
        mint s(N / i);
        s = s * (s+1) / 2;
        ans += s * s * (F[j] - F[i-1]);
    }
    ans -= (mint)N * (mint)(N+1) / (mint)2;
    ans /= 2;

    cout << ans;
    return 0;
}
