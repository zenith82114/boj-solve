/*
 * Q27293 - Lagrange interpolation
 * Date: 2023.12.27
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    constexpr static int MOD = 1'000'000'007;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) { if (val < 0) val += MOD; }
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

mint solve(int n, int d, const vector<mint>& f) {
    if (n <= d+1) return f[n];
    mint x(1); for (int i = 0; i <= d+1; ++i) x *= n-i;
    mint y(1); for (int i = 1; i <= d+1; ++i) y *= -i;
    y = y.inv();
    mint ans(0);
    for (int i = 0; i <= d+1; ++i) {
        ans += x/(n-i)*y*f[i];
        y /= i+1; y *= i-d-1;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc; while (tc--) {
        int a, b, d; cin >> a >> b >> d;
        if (!d) { cout << b-a+1 << '\n'; continue; }

        vector<mint> f(d+2);
        for (int i = 1; i <= d+1; ++i) f[i] = f[i-1] + mint(i).pow(d);
        cout << solve(b, d, f) - solve(a-1, d, f) << '\n';
    }

    return 0;
}
