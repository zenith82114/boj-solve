/*
 * Q17467a - Lagrange interpolation + FFT
 * Date: 2023.5.19
 *
 * Disclaimer: hugely aided by ho94949's original solution
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using cpx = complex<double>;
const double PI = acos(-1.);

struct mint {
    static int MOD;
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

void fft(vector<cpx>& A, bool inv = false) {
    int N = A.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(A[i], A[j]);
    }
    for (int n = 1; n < N; n <<= 1) {
        double theta = (inv? -PI : PI) / n;
        for (int m = 0; m < N; m += n<<1) {
            for (int i = 0, j = n; i < n; ++i, ++j) {
                cpx a(A[m | i]);
                cpx b(A[m | j] * polar(1., i * theta));
                A[m | i] = a + b;
                A[m | j] = a - b;
            }
        }
    }
    if (inv) for (cpx& a : A) a /= N;
}

vector<mint> convolve(const vector<mint>& A, const vector<mint>& B) {
    int sA = A.size(), sB = B.size();
    int sC = sA + sB - 1;
    int N = 1; while (N < sC) N <<= 1;

    vector<cpx> A0(N), A1(N), B0(N), B1(N);
    for (int i = 0; i < sA; ++i) {
        A0[i] = A[i].val & 32767;
        A1[i] = A[i].val >> 15;
    }
    for (int i = 0; i < sB; ++i) {
        B0[i] = B[i].val & 32767;
        B1[i] = B[i].val >> 15;
    }
    fft(A0), fft(A1), fft(B0), fft(B1);

    vector<cpx> C0(N), C1(N), C2(N);
    for (int i = 0; i < N; ++i) {
        C0[i] = A0[i] * B0[i];
        C1[i] = A0[i] * B1[i] + A1[i] * B0[i];
        C2[i] = A1[i] * B1[i];
    }
    fft(C0, true), fft(C1, true), fft(C2, true);

    vector<mint> C(sC);
    const int P = mint::MOD;
    for (int i = 0; i < sC; ++i) {
        i64 c0 = llround(C0[i].real()) % P;
        i64 c1 = llround(C1[i].real()) % P;
        i64 c2 = llround(C2[i].real()) % P;
        c1 += c2 << 15; c1 %= P;
        c0 += c1 << 15; C[i] = c0 % P;
    }
    return C;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N >> mint::MOD;

    vector<mint> f        { 1, 2 };
    vector<mint> fact     { 1 };
    vector<mint> fact_inv { 1 };
    vector<mint> inv      { 0 };

    int d = 1;
    for (; d*(d + 1) < N; d <<= 1) {
        for (int i = fact.size(); i < 4*d + 2; ++i)
            fact.emplace_back(fact.back() * i);

        fact_inv.resize(fact.size());
        fact_inv.back() = fact.back().inv();
        for (int i = 4*d; fact_inv[i] == 0; --i)
            fact_inv[i] = fact_inv[i+1] * (i+1);

        for (int i = inv.size(); i < 4*d + 2; ++i)
            inv.emplace_back(fact[i-1] * fact_inv[i]);

        vector<mint> g(d + 1);
        for (int i = 0; i <= d; ++i) {
            g[i] = f[i] * fact_inv[i] * fact_inv[d - i];
            if ((d ^ i) & 1) g[i] = -g[i];
        }

        auto h = convolve(g, inv);
        for (int i = 0; i <= d; ++i) h[i] = f[i];
        for (int i = d + 1; i < 4*d + 2; ++i)
            h[i] *= fact[i] * fact_inv[i - d - 1];

        f.resize(2*d + 1);
        for (int i = 0; i <= 2*d; ++i)
            f[i] = h[2*i] * h[2*i + 1];
    }

    mint ans(1);
    int i = 0;
    for (; (i + 1)*d <= N; ++i) ans *= f[i];
    for (i = i*d + 1; i <= N; ++i) ans *= i;
    cout << ans;
    return 0;
}
