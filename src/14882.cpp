/*
 * Q14882 - FFT
 * Date: 2023.2.1
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MOD = 786'433;

struct mint {
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

vector<mint> dnc(const vector<mint>& A, mint g, int r) {
    if (A.size() == 1) {
        return vector<mint>(r+1, A[0]);
    }
    if (r == 1) {
        mint b(0);
        for (const mint& a : A) b += a;
        return { 0, b };
    }

    vector<mint> Ae;
    for (size_t i = 0; i < A.size(); i += 2) Ae.emplace_back(A[i]);
    vector<mint> Be = dnc(Ae, g * g, r>>1);
    vector<mint> Ao;
    for (size_t i = 1; i < A.size(); i += 2) Ao.emplace_back(A[i]);
    vector<mint> Bo = dnc(Ao, g * g, r>>1);

    vector<mint> B(r+1);
    mint h(1);
    for (int i = 1; i <= r>>1; ++i) {
        h *= g;
        B[i] = Be[i] + h * Bo[i];
    }
    for (int i = 1; i <= r>>1; ++i) {
        h *= g;
        B[i + (r>>1)] = Be[i] + h * Bo[i];
    }
    return B;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<mint> A(N+1);
    for (mint& a : A) cin >> a;

    const mint g(11);
    vector<mint> B = dnc(A, g, MOD-1);

    vector<int> dlog(MOD);
    mint h(1);
    for (int i = 1; i < MOD; ++i) {
        h *= g;
        dlog[h.val] = i;
    }

    int K; cin >> K;
    while (K--) {
        mint x; cin >> x;
        cout << (x != 0? B[dlog[x.val]] : A[0]) << '\n';
    }

    return 0;
}
