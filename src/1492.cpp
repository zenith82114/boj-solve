/*
 * Q1492 - Combinatorics + DP
 * Date: 2024.5.4
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    constexpr static int MOD = 1'000'000'007;
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        int v; is >> v; x = mint(v); return is;
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
    bool operator!() const { return !val; }
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
        val = (1LL * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    mint s[60], comb[60][60];
    int n, k; cin >> n >> k;

    for (int i = 0; i <= k+1; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j < i; ++j) {
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
        comb[i][i] = 1;
    }

    mint p(1);

    for (int j = 0; j <= k; ++j) {
        p *= n+1;
        s[j] = p - 1;
        for (int i = 0; i < j; ++i) {
            s[j] -= comb[j+1][i] * s[i];
        }
        s[j] /= j+1;
    }

    cout << s[k];
    return 0;
}
