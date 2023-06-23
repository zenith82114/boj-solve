/*
 * Q17468 - Lagrange interpolation + FFT
 * Date: 2023.6.15
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using cpx = complex<double>;
const double PI = acos(-1.);

struct mint {
    static i64 MOD;
    i64 val;
    mint(): val(0) {}
    mint(i64 v): val(v) {}
    mint(const mint& x): val(x.val) {}

    mint operator-() const { return mint(val? MOD - val : 0); }
    mint pow(i64 e) const {
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
        val = ((__int128_t)val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};
i64 mint::MOD = 0;

void fft(vector<cpx>& A, bool inv = false) {
    int N = A.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(A[i], A[j]);
    }

    vector<cpx> roots(N>>1);
    double theta = (inv? -2. : 2.) * PI / N;
    for (int i = 0; i < N>>1; ++i) roots[i] = polar(1., i * theta);

    for (int n = 1; n < N; n <<= 1) {
        int step = (N>>1) / n;
        for (int m = 0; m < N; m += n<<1) {
            for (int i = 0, j = n; i < n; ++i, ++j) {
                cpx a = A[m | i];
                cpx b = A[m | j] * roots[i * step];
                A[m | i] = a + b;
                A[m | j] = a - b;
            }
        }
    }
    if (inv) for (cpx& a : A) a /= N;
}

vector<mint> convolve(const vector<mint>& A, const vector<mint>& B, int sB) {
    int sA = A.size();
    int sC = sA + sB - 1;
    int N = 1; while (N < sC) N <<= 1;

    vector<cpx> P(N), Q(N);
    for (int i = 0; i < sA; ++i)
        P[i] = cpx(A[i].val >> 17, A[i].val & 0x01ffff);
    for (int i = 0; i < sB; ++i)
        Q[i] = cpx(B[i].val >> 17, B[i].val & 0x01ffff);
    fft(P); fft(Q);

    vector<cpx> R0(N), R1(N);
    for (int i = 0; i < N; ++i) {
        int j = i? (N - i) : 0;
        cpx p0 = (P[i] + conj(P[j])) * cpx(.5, 0);
        cpx p1 = (P[i] - conj(P[j])) * cpx(0, -.5);
        cpx q0 = (Q[i] + conj(Q[j])) * cpx(.5, 0);
        cpx q1 = (Q[i] - conj(Q[j])) * cpx(0, -.5);
        R0[i] = p0 * (q0 + q1 * cpx(0, 1));
        R1[i] = p1 * (q0 + q1 * cpx(0, 1));
    }
    fft(R0, true); fft(R1, true);

    vector<mint> C(sC);
    const i64 MOD = mint::MOD;
    for (int i = 0; i < sC; ++i) {
        i64 c0 = llround(R0[i].real()) % MOD;
        i64 c1 = llround(R0[i].imag() + R1[i].real()) % MOD;
        i64 c2 = llround(R1[i].imag()) % MOD;
        c1 += c0 << 17; c1 %= MOD;
        c2 += c1 << 17; C[i] = c2 % MOD;
    }
    return C;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    i64 N; cin >> N >> mint::MOD;

    i64 D = 1;
    while (D*(D + 1) < N) D <<= 1;

    vector<mint> fact(4*D + 2);
    fact[0] = 1;
    for (i64 i = 1; i < 4*D + 2; ++i)
        fact[i] = fact[i-1] * i;

    vector<mint> fact_inv(4*D + 2);
    i64 j = min(4*D + 1, mint::MOD - 1);
    fact_inv[j] = fact[j].inv();
    for (i64 i = j - 1; i >= 0; --i)
        fact_inv[i] = fact_inv[i+1] * (i+1);

    vector<mint> inv(4*D + 2);
    for (i64 i = 1; i < 4*D + 2; ++i)
        inv[i] = fact[i-1] * fact_inv[i];

    vector<mint> f(4*D + 2);
    f[0] = 1; f[1] = 2;

    for (i64 d = 1; d < D; d <<= 1) {
        vector<mint> g(d + 1);
        for (i64 i = 0; i <= d; ++i) {
            g[i] = f[i] * fact_inv[i] * fact_inv[d - i];
            if ((d ^ i) & 1) g[i] = -g[i];
        }

        auto h = convolve(g, inv, 4*d + 2);
        for (i64 i = 0; i <= d; ++i) h[i] = f[i];
        for (i64 i = d + 1; i < 4*d + 2; ++i)
            h[i] *= fact[i] * fact_inv[i - d - 1];

        for (i64 i = 0; i <= 2*d; ++i)
            f[i] = h[2*i] * h[2*i + 1];
    }

    mint ans(1);
    i64 i = 0;
    for (; (i + 1)*D <= N; ++i) ans *= f[i];
    for (i = i*D + 1; i <= N; ++i) ans *= i;
    cout << ans.val;

    return 0;
}
