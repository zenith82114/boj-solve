/*
 * Q18354 - Chirp Z-transform
 * Date: 2023.6.16
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using cpx = complex<double>;
const double PI = acos(-1.);
constexpr int MOD = 1030307;

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

vector<mint> convolve(const vector<mint>& A, const vector<mint>& B) {
    int sA = A.size(), sB = B.size();
    int sC = sA + sB - 1;
    int N = 1; while (N < sC) N <<= 1;

    vector<cpx> P(N), Q(N);
    for (int i = 0; i < sA; ++i)
        P[i] = cpx(A[i].val >> 10, A[i].val & 1023);
    for (int i = 0; i < sB; ++i)
        Q[i] = cpx(B[i].val >> 10, B[i].val & 1023);
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
    for (int i = 0; i < sC; ++i) {
        i64 c0 = llround(R0[i].real()) % MOD;
        i64 c1 = llround(R0[i].imag() + R1[i].real()) % MOD;
        i64 c2 = llround(R1[i].imag()) % MOD;
        c1 += c0 << 10; c1 %= MOD;
        c2 += c1 << 10; C[i] = c2 % MOD;
    }
    return C;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    const mint w(2), w_inv(515154);
    vector<mint> w_pow(MOD), w_inv_pow(MOD);
    vector<int> dlog(MOD);

    w_pow[0] = 1;
    w_inv_pow[0] = 1;
    for (int i = 1; i < MOD; ++i) {
        w_pow[i] = w * w_pow[i-1];
        w_inv_pow[i] = w_inv * w_inv_pow[i-1];
        dlog[w_pow[i].val] = i;
    }

    int N; cin >> N; ++N;
    vector<mint> X(N);
    for (mint& x : X) cin >> x;

    auto nC2 = [] (i64 n) -> int {
        return ((n * (n-1)) >> 1) % (MOD - 1);
    };

    vector<mint> A(N + 1), B(N + MOD);
    for (int i = 1; i <= N; ++i)
        A[i] = X[N - i] * w_inv_pow[nC2(N - i)];
    for (int i = 0; i < N + MOD; ++i)
        B[i] = w_pow[nC2(i)];

    auto C = convolve(A, B);

    vector<mint> Y(MOD);
    for (int i = 0; i < MOD; ++i)
        Y[i] = C[N + i] * w_inv_pow[nC2(i)];

    int K; cin >> K;
    while (K--) {
        int x; cin >> x;
        cout << (x? Y[dlog[x]] : X[0]) << '\n';
    }

    return 0;
}
