/*
 * Q15572 - Bostan-Mori alg.
 * Date: 2025.7.23
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MOD = 1999;

struct mint {
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
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};
using poly = vector<mint>;

void poly_mul(poly& A, const poly& B) {
    int a = A.size(), b = B.size();
    if (!a || !b) {
        A.clear();
        return;
    }
    poly C(a + b - 1);
    for (int i = 0; i < a; ++i)
    for (int j = 0; j < b; ++j) C[i + j] += A[i] * B[j];
    A.swap(C);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N; i64 M; cin >> N >> M;

    poly P = {1};
    if (N > 1) P.emplace_back(1);
    for (int i = 2; i < N; ++i) P.emplace_back(P.back() * 2);

    poly Q(N + 1, MOD - 1);
    Q[0] = 1;
    Q[N] = -mint(2).pow(N - 1);

    poly_mul(P, Q);
    P.resize(N);

    for (i64 e = M; e; e >>= 1) {
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

    cout << (P[0] / Q[0]);
    return 0;
}
