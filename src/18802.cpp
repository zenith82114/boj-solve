/*
 * Q18802 - DP, combinatorics
 * Date: 2024.12.14
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    static int MOD;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {}
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        return is >> x.val;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(val? MOD - val : 0); }
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
int mint::MOD = 0;

mint dp[5][3001] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n >> mint::MOD;
    dp[0][0] = 1;
    mint h[5];
    h[0] = 1;

    for (int m = 1; m <= (n - 1)/2; ++m) {
        mint g;
        for (int i = 0; i < 4; ++i) g += dp[i][m - 1];
        for (int i = 1; i < 5; ++i) h[i] = h[i - 1] * (g + i - 1) / i;

        for (int i = 4; i > 0; --i)
        for (int j = n; j >= m; --j)
        for (int c = 1; c <= i; ++c) {
            int k = j - c*m;
            if (k >= 0) dp[i][j] += h[c] * dp[i - c][k];
        }
    }

    mint ans;
    for (int i = 0; i < 5; ++i) ans += dp[i][n - 1];
    if (~n & 1) {
        mint g;
        for (int i = 0; i < 4; ++i) g += dp[i][n/2 - 1];
        ans += g * (g + 1) / 2;
    }
    cout << ans;
    return 0;
}
