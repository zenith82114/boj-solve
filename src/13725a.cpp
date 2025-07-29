/*
 * Q13725a - Bostan-Mori alg.
 * Date: 2022.12.18
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MOD = 104857601;

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

constexpr int BASE_ROOT = 39193363;
constexpr int BASE_ROOT_IDX = 22;
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

void trim(poly& A) {
    while (!A.empty() && A.back() == mint(0)) A.pop_back();
}

void trim(poly& A, size_t sz) {
    if (sz < A.size()) A.resize(sz);
    trim(A);
}

void poly_mul(poly& A, poly& B) {
    int a = A.size(), b = B.size();
    if (!(a && b)) {
        A.clear();
        return;
    }
    size_t sz = [](int n) {
        if (n & (n -1)) {
            for (int i = 1; i < 32; i <<= 1) n |= (n >> i);
            return n +1;
        }
        return n;
    }(a + b -1);

    A.resize(sz, 0); ntt(A, false);
    B.resize(sz, 0); ntt(B, false);
    for (size_t i = 0; i < sz; ++i) A[i] *= B[i];
    ntt(A, true); trim(A);
    ntt(B, true); trim(B);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // preprocess for NTT
    roots[BASE_ROOT_IDX] = mint(BASE_ROOT);
    for (int i = BASE_ROOT_IDX; i; --i)
        roots[i-1] = roots[i] * roots[i];
    for (int i = 1; i <= BASE_ROOT_IDX; ++i)
        roots_inv[i] = roots[i].inv();

    int K; cin >> K;
    int64_t N; cin >> N; N--;
    poly P(K);
    for (mint& p : P) cin >> p;
    poly Q(K+1);
    Q[0] = 1;
    for (int i = 1; i <= K; ++i) {
        mint& q = Q[i]; cin >> q; q = -q;
    }
    poly_mul(P, Q);
    trim(P, K);

    for (; N; N >>= 1) {
        poly Qm = Q;
        for (size_t i = 1; i < Qm.size(); i += 2) Qm[i] = -Qm[i];

        poly_mul(P, Qm);
        poly P_;
        for (size_t i = N&1; i < P.size(); i += 2) P_.emplace_back(P[i]);
        P.swap(P_);

        poly_mul(Q, Qm);
        poly Q_;
        for (size_t i = 0; i < Q.size(); i += 2) Q_.emplace_back(Q[i]);
        Q.swap(Q_);
    }
    cout << P[0]/Q[0] << '\n';

    return 0;
}
