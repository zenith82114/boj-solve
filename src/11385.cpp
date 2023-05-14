/*
 * Q11385 - NTT + Chinese Remainder Theorem
 * Date: 2023.5.14
 */

#include<bits/stdc++.h>
using namespace std;

template <int MOD>
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

template <int MOD, int ROOT, int INDEX>
class ntt {
    using mint_t = mint<MOD>;
    array<mint_t, INDEX + 1> rou, irou;
public:
    ntt() {
        rou[INDEX] = mint_t(ROOT);
        irou[INDEX] = mint_t(ROOT).inv();
        for (int i = INDEX; i; --i) {
            rou[i-1] = rou[i] * rou[i];
            irou[i-1] = irou[i] * irou[i];
        }
    }
    void run(vector<mint_t>& A, bool inv) {
        int N = A.size();
        for (int i = 1, j = 0; i < N; ++i) {
            int t = N>>1;
            for (; j & t; t >>= 1) j ^= t;
            j ^= t;
            if (i < j) swap(A[i], A[j]);
        }
        for (int n = 2, rn = 1; n <= N; n <<= 1, ++rn) {
            mint_t w(inv ? irou[rn] : rou[rn]);
            for (int m = 0; m < N; m += n) {
                mint_t z(1);
                for (int i = 0, j = n>>1; j < n; ++i, ++j) {
                    mint_t a(A[m|i]);
                    mint_t b(A[m|j] * z);
                    A[m|i] = a + b;
                    A[m|j] = a - b;
                    z *= w;
                }
            }
        }
        if (inv) {
            mint_t iN(mint_t(N).inv());
            for (mint_t& a : A) a *= iN;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    constexpr int P1 = 119<<23|1; ntt<P1,  15311432, 23> ntt1;
    constexpr int P2 = 483<<21|1; ntt<P2, 673144645, 21> ntt2;

    int N, M; cin >> N >> M;
    vector<mint<P1> > A1(N+1), B1(M+1);
    vector<mint<P2> > A2(N+1), B2(M+1);
    for (int i = 0; i <= N; ++i) { cin >> A1[i]; A2[i] = A1[i].val; }
    for (int i = 0; i <= M; ++i) { cin >> B1[i]; B2[i] = B1[i].val; }

    int sz = 1; while (sz <= N + M) sz <<= 1;

    A1.resize(sz); ntt1.run(A1, false);
    B1.resize(sz); ntt1.run(B1, false);
    for (int i = 0; i < sz; ++i) A1[i] *= B1[i];
    ntt1.run(A1, true);

    A2.resize(sz); ntt2.run(A2, false);
    B2.resize(sz); ntt2.run(B2, false);
    for (int i = 0; i < sz; ++i) A2[i] *= B2[i];
    ntt2.run(A2, true);

    using i64 = int64_t;
    constexpr i64 Q = (i64)P1 * P2;
    const auto mul_mod64 = [&Q] (int a, i64 b) {
        i64 c = 0;
        for (; a; a >>= 1) {
            if (a&1) c += b, c = c >= Q? c - Q : c;
            b <<= 1, b = b >= Q? b - Q : b;
        }
        return c;
    };

    i64 ans = 0;
    for (int i = 0; i <= N + M; ++i) {
        i64 x = mul_mod64(A1[i].val, 1011146010407206845LL);
        x += mul_mod64(A2[i].val, 68878860357LL);
        x = x < Q? x : x - Q;
        ans ^= x;
    }
    cout << ans;
    return 0;
}
