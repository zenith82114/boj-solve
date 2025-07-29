/*
 * Q13575 - NTT
 * Date: 2025.7.30
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MOD = 7<<26|1;

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

using poly = vector<mint>;

constexpr int BASE_ROOT = 2187;
constexpr int BASE_ROOT_IDX = 26;
array<mint, BASE_ROOT_IDX + 1> roots, roots_inv;

void ntt(poly& A, const bool inv) {
    int N = A.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(A[i], A[j]);
    }
    for (int n = 2, rn = 1; n <= N; n <<= 1, ++rn) {
        mint w(inv ? roots_inv[rn] : roots[rn]);
        for (int m = 0; m < N; m += n) {
            mint z(1);
            for (int i = 0, j = n>>1; j < n; ++i, ++j) {
                mint a(A[m|i]);
                mint b(A[m|j] * z);
                A[m|i] = a + b;
                A[m|j] = a - b;
                z *= w;
            }
        }
    }
    if (inv) for (mint& a : A) a /= N;
}

size_t po2(size_t n) {
    if (n & (n - 1)) {
        for (int i = 1; i < 32; i <<= 1) n |= (n>>i);
        return n + 1;
    }
    return n;
}

void trim(poly& A) {
    while (!A.empty() && !A.back().val) A.pop_back();
}

void poly_mul(poly& A, poly& B) {
    int a = A.size(), b = B.size();
    if (!(a && b)) { A.clear(); return; }
    size_t sz = po2(a + b - 1);
    A.resize(sz, 0); ntt(A, false);
    B.resize(sz, 0); ntt(B, false);
    for (size_t i = 0; i < sz; ++i) A[i] *= B[i];
    ntt(A, true); trim(A);
    ntt(B, true); trim(B);
}

void poly_sqr(poly& A) {
    if (A.empty()) return;
    size_t sz = po2(2*A.size() - 1);
    A.resize(sz, 0); ntt(A, false);
    for (auto& a : A) a *= a;
    ntt(A, true); trim(A);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    roots[BASE_ROOT_IDX] = mint(BASE_ROOT);
    roots_inv[BASE_ROOT_IDX] = mint(BASE_ROOT).inv();
    for (int i = BASE_ROOT_IDX; i; --i) {
        roots[i - 1] = roots[i] * roots[i];
        roots_inv[i - 1] = roots_inv[i] * roots_inv[i];
    }

    poly A(1001), B {1};
    int n, k; cin >> n >> k;
    while (n--) { int x; cin >> x; A[x] = 1; }
    trim(A);
    for (; k; k /= 2) {
        if (k & 1) {
            poly_mul(B, A);
            for (auto& b : B) b.val = min(b.val, 1);
        }
        poly_sqr(A);
        for (auto& a : A) a.val = min(a.val, 1);
    }
    for (size_t i = 0; i < B.size(); ++i) if (B[i].val) cout << i << ' ';
    return 0;
}
