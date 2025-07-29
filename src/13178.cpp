/*
 * Q13178 - Bostan-Mori alg.
 * Date: 2024.4.10
 */

#include<bits/stdc++.h>
using namespace std;

// Caution: 2*(MOD-1) > INT32_MAX
constexpr uint MOD = 1092616193;
constexpr  int BASE_ROOT = 633127788;
constexpr  int BASE_ROOT_IDX = 21;

struct mint {
    uint val;
    mint(): val(0) {}
    mint(uint v): val(v) { if (v >= MOD) v %= MOD; }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        return is >> x.val;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(val? MOD - val : 0); }
    mint pow(uint e) const {
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
        if ((val += MOD - x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1ull * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

using poly = vector<mint>;

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
        if (n & (n-1)) {
            for (int i = 1; i < 32; i <<= 1) n |= (n >> i);
            return n +1;
        }
        return n;
    }(a+b-1);

    A.resize(sz, 0); ntt(A, false);
    B.resize(sz, 0); ntt(B, false);
    for (size_t i = 0; i < sz; ++i) A[i] *= B[i];
    ntt(A, true); trim(A);
    ntt(B, true); trim(B);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // preprocess for NTT
    roots[BASE_ROOT_IDX] = mint(BASE_ROOT);
    for (int i = BASE_ROOT_IDX; i; --i)
        roots[i-1] = roots[i] * roots[i];
    for (int i = 1; i <= BASE_ROOT_IDX; ++i)
        roots_inv[i] = roots[i].inv();

    int N; cin >> N;
    uint64_t M; cin >> M;

    poly Q(N+2);
    mint isq;
    for (int i = N+1; i > 1; --i) {
        cin >> Q[i];
        isq += Q[i];
    }
    isq = isq.inv();
    Q[0] = 1;
    Q[1] = (-Q[2])*isq - 1;
    for (int i = 2; i <= N; ++i) Q[i] = (Q[i] - Q[i+1])*isq;
    Q[N+1] *= isq;

    poly P(N+1);
    P[N] = 1;

    for (uint64_t e = M; e; e >>= 1) {
        poly Qm = Q;
        for (size_t i = 1; i < Qm.size(); i += 2) Qm[i] = -Qm[i];

        poly_mul(P, Qm);
        poly P_;
        for (size_t i = e&1; i < P.size(); i += 2) P_.emplace_back(P[i]);
        P.swap(P_);

        poly_mul(Q, Qm);
        poly Q_;
        for (size_t i = 0; i < Q.size(); i += 2) Q_.emplace_back(Q[i]);
        Q.swap(Q_);
    }

    cout << (P[0]/Q[0]) << '\n';
    return 0;
}
