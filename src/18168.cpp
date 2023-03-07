/*
 * Q18168 - Multipoint evaluation
 * Date: 2023.3.6
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MOD = 998'244'353;

struct mint {
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        int v; cin >> v; x = mint(v); return is;
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
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};
using poly = vector<mint>;

constexpr int BASE_ROOT = 15'311'432;
constexpr int BASE_ROOT_IDX = 23;
array<mint, BASE_ROOT_IDX + 1> rou, irou;

void ntt(poly& A, const bool inv) {
    int N = A.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(A[i], A[j]);
    }
    for (int n = 2, rn = 1; n <= N; n <<= 1, ++rn) {
        mint w(inv ? irou[rn] : rou[rn]);
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
    if (inv) {
        mint iN(mint(N).inv());
        for (mint& a : A) a *= iN;
    }
}

void trim(poly& A, size_t sz = ULONG_MAX) {
    if (sz < A.size()) A.resize(sz);
    while (!A.empty() && !A.back()) A.pop_back();
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

poly poly_inv(const poly& A, int m) {
    int sz = A.size();
    poly R = { A[0].inv() };
    for (int k = 1; k < m; k <<= 1) {
        poly S(A.begin(), A.begin() + min(sz, k<<1));
        poly_mul(S, R);
        for (mint& s : S) s *= -1;
        S[0] += 2;
        poly_mul(R, S);
        trim(R, k<<1);
    }
    trim(R, m);
    return R;
}

poly poly_mod(const poly& A, poly B) {
    int a = A.size(), b = B.size();
    if (a < b) return A;

    poly rA(A), rB(B);
    reverse(rA.begin(), rA.end()); trim(rA);
    reverse(rB.begin(), rB.end()); trim(rB);

    rB = poly_inv(rB, a-b+1);
    poly_mul(rA, rB);
    rA.resize(a-b+1, 0);
    reverse(rA.begin(), rA.end());
    poly_mul(B, rA);

    poly R(b-1);
    for (int i = 0; i < b-1; ++i) R[i] = A[i] - B[i];
    trim(R);
    return R;
}

vector<poly> segt;
vector<mint> X, Y;

void build_segt(int n, int s, int e) {
    if (s != e) {
        int m = (s + e)>>1;
        build_segt(n<<1, s, m);
        build_segt(n<<1|1, m+1, e);
        segt[n] = segt[n<<1];
        poly_mul(segt[n], segt[n<<1|1]);
    }
    else segt[n] = { -X[s], 1 };
}

void dnc(int n, int s, int e, const poly& A) {
    if (s != e) {
        int m = (s + e)>>1;
        poly B = poly_mod(A, segt[n]);
        dnc(n<<1, s, m, B);
        dnc(n<<1|1, m+1, e, B);
    }
    else {
        Y[s] = A[0];
        if (A.size() > 1) Y[s] += A[1] * X[s];
        if (A.size() > 2) Y[s] += A[2] * X[s] * X[s];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    rou[BASE_ROOT_IDX] = mint(BASE_ROOT);
    irou[BASE_ROOT_IDX] = mint(BASE_ROOT).inv();
    for (int i = BASE_ROOT_IDX; i; --i) {
        rou[i-1] = rou[i] * rou[i];
        irou[i-1] = irou[i] * irou[i];
    }

    int N, Q; cin >> N >> Q;

    poly A(N+1);
    for (int i = N; ~i; cin >> A[i--]);
    trim(A);

    X.resize(Q);
    for (mint& x : X) cin >> x;

    int sz = 1;
    for (; sz < Q; sz <<= 1);
    segt.resize(sz<<1);
    build_segt(1, 0, Q-1);

    Y.resize(Q);
    dnc(1, 0, Q-1, A);

    for (mint& y : Y) cout << y << '\n';
    return 0;
}
