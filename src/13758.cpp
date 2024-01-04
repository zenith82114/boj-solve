/*
 * Q13758 - Fast Walsh-Hadamard transform
 * Date: 2024.1.4
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    constexpr static int MOD = 30011;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {
        if (val >= MOD) val %= MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        return is >> x.val;
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
        val = (val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

void fwht(vector<mint>& f, bool inv = false) {
    for (int d = 1; d < 65536; d *= 2)
    for (int x = 0; x < 65536; x += 2*d)
    for (int i = 0; i < d; ++i) {
        mint a0 = f[x|i], a1 = f[x|d|i];
        f[x|i] = a0 + a1;
        f[x|d|i] = a0 - a1;
    }
    if (inv) for (mint& a : f) a /= 65536;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<mint> f(65536); fill_n(f.begin(), k+1, 1);
    fwht(f);
    for (auto& a : f) a = a.pow(n);
    fwht(f, true);
    cout << mint(k+1).pow(n) - f[0];
    return 0;
}
