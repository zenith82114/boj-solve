/*
 * Q13725 - Kitamasa + NTT
 * Date: 2022.7.21
 */

#include<bits/stdc++.h>
using namespace std;

#define MOD 104857601
#define PRIM_ROOT 39193363
#define PRIM_ROOT_IDX 22

struct mint {
    int val;
    mint() : val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& v) : val(v.val) {}
    mint operator+(const mint &that) const {
        return mint(val) += that;
    }
    mint& operator+=(const mint &that) {
        val = (val + that.val) % MOD;
        return *this;
    }
    mint operator-(const mint &that) const {
        return mint(val) -= that;
    }
    mint& operator-=(const mint &that) {
        val = (val + MOD - that.val) % MOD;
        return *this;
    }
    mint operator*(const mint &that) const {
        return mint(val) *= that;
    }
    mint& operator*=(const mint &that) {
        val = (int)((1ll * val * that.val) % MOD);
        return *this;
    }
    mint operator/(const mint &that) const {
        return mint(val) *= that.inv();
    }
    mint& operator/=(const mint &that) {
        return (*this) *= that.inv();
    }
    bool operator!() const {
        return !val;
    }
    mint pow(int exp) const {
        mint res(1), tmp(val);
        while (exp) {
            if (exp & 1) res *= tmp;
            exp >>= 1;
            tmp *= tmp;
        }
        return res;
    }
    mint inv() const {
        return pow(MOD-2);
    }
};

using poly = vector<mint>;
array<mint, PRIM_ROOT_IDX + 1> roots, roots_inv;

inline int ceil_pow2(int n) {
    if (n & (n-1)) {
        for (int i = 1; i < 32; i <<= 1)
            n |= (n >> i);
        return n+1;
    }
    return n;
}

void shrink(poly& A) {
    while (A.size() && !A.back())
        A.pop_back();
}

void trunc(poly& A, int n) {
    if ((int)A.size() > n)
        A.resize(n);
    shrink(A);
}

void ntt(poly& A, const bool inv) {
    int N = A.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1)
            j ^= t;
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
                A[m|i] = a+b;
                A[m|j] = a-b;
                z *= w;
            }
        }
    }
    if (inv) for (mint& a : A)
        a /= N;
}

poly poly_mul(poly A, poly B) {
    int a = A.size(), b = B.size();
    if (!(a && b)) return poly({});

    int sz = ceil_pow2(a+b-1);
    A.resize(sz, 0);
    B.resize(sz, 0);
    ntt(A, false);
    ntt(B, false);
    for (int i = 0; i < sz; ++i)
        A[i] *= B[i];
    ntt(A, true);
    shrink(A);
    return A;
}

poly poly_inv(poly A, int m) {
    int sz = A.size();
    poly R = { A[0].inv() };
    for (int k = 1; k < m; k <<= 1) {
        poly S(A.begin(), A.begin() + min(sz, k<<1));
        S = poly_mul(S, R);
        for (mint& s : S) s *= -1;
        S[0] += 2;
        R = poly_mul(R, S);
        trunc(R, k<<1);
    }
    trunc(R, m);
    return R;
}

poly poly_mod(poly A, poly B) {
    int a = A.size(), b = B.size();
    if (a < b)
        return A;

    poly rA(A), rB(B);
    reverse(rA.begin(), rA.end());
    shrink(rA);
    reverse(rB.begin(), rB.end());
    shrink(rB);

    rA = poly_mul(rA, poly_inv(rB, a-b+1));
    rA.resize(a-b+1, 0);
    reverse(rA.begin(), rA.end());

    B = poly_mul(B, rA);
    poly R(b-1);
    for (int i = 0; i < b-1; ++i)
        R[i] = A[i] - B[i];
    shrink(R);
    return R;
}

poly kitamasa(poly C, int64_t n) {
    poly D = { 1 };
    poly F = { 0, 1 };
    reverse(C.begin(), C.end());
    for (mint& c : C) c *= -1;
    C.emplace_back(1);

    while (n) {
        if (n & 1)
            D = poly_mod(poly_mul(D, F), C);
        n >>= 1;
        F = poly_mod(poly_mul(F, F), C);
    }
    return D;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    // preprocess roots for NTT
    roots[PRIM_ROOT_IDX] = mint(PRIM_ROOT);
    for (int i = PRIM_ROOT_IDX; i; --i)
        roots[i-1] = roots[i] * roots[i];
    for (int i = 1; i <= PRIM_ROOT_IDX; ++i)
        roots_inv[i] = roots[i].inv();

    int k; cin >> k;
    int64_t N; cin >> N;
    poly A(k), C(k);
    for (mint& a : A) cin >> a.val;
    for (mint& c : C) cin >> c.val;

    mint ans(0);
    poly D = kitamasa(C, N-1);
    for (int i = 0; i < (int)D.size(); ++i)
        ans += A[i] * D[i];

    cout << ans.val << '\n';
    return 0;
}
