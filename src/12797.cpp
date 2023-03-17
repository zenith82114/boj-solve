/*
 * Q12797 - DP + Linear algebra
 * Date: 2023.3.17
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<mint> A(M);
    for (mint& a : A) cin >> a;

    vector<vector<mint> > Q(M, vector<mint>(M));
    for (int j = 0; j < M; ++j) {
        Q[j][j] = 1;
        for (int i = j+1; i < M; ++i)
            Q[i][j] = Q[i-1][j] * A[j] / (A[j] - A[i]);
    }

    vector<mint> B(M);
    for (int i = 0; i < M; ++i) {
        B[i] = 1;
        for (int j = 0; j < i; ++j)
            B[i] -= Q[i][j] * B[j];
    }

    for (int i = 0; i < M; ++i) B[i] *= A[i].pow(N);

    mint ans;
    for (int i = 0; i < M; ++i) ans += Q[M-1][i] * B[i];

    cout << ans;
    return 0;
}
