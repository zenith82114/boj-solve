/*
 * Q13428 - NTT
 * Date: 2025.2.4
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MAXD = 100000;
constexpr int lgK = 3, K = 1<<lgK;
constexpr int N = 2 * (1<<17) * K;

constexpr int MOD = 469762049;
constexpr int PRIM_ROOT = 2187;
constexpr int PRIM_ROOT_IDX = 26;

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

int a[MAXD] {}, b[MAXD] {}, c[2 * MAXD] {};
mint f[N] {}, g[N] {};
array<mint, PRIM_ROOT_IDX + 1> roots, roots_inv;
vector<int> va, vb;

void ntt(mint A[], const bool inv = false) {
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(A[i], A[j]);
    }
    for (int n = 2, rn = 1; n <= N; n <<= 1, ++rn) {
        mint w((inv ? roots_inv : roots)[rn]);
        for (int m = 0; m < N; m += n) {
            mint z(1);
            for (int i = 0, j = n>>1; j < n; ++i, ++j) {
                mint a(A[m | i]);
                mint b(A[m | j] * z);
                A[m | i] = a + b;
                A[m | j] = a - b;
                z *= w;
            }
        }
    }
    if (inv) for (int i = 0; i < N; ++i) A[i] /= N;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    roots[PRIM_ROOT_IDX] = mint(PRIM_ROOT);
    for (int i = PRIM_ROOT_IDX; i; --i) roots[i-1] = roots[i] * roots[i];
    for (int i = 1; i <= PRIM_ROOT_IDX; ++i) roots_inv[i] = roots[i].inv();

    int n; cin >> n;
    for (int i = 0; i < n; ++i) { int x; cin >> x; ++a[x]; }
    for (int i = 0; i < n; ++i) { int x; cin >> x; ++b[x]; }
    for (int x = 0; x < MAXD; ++x) {
        if (a[x] >= K) va.emplace_back(x);
        for (int k = 0; k < K; ++k) f[x<<lgK | k] = a[x] > k? 1 : 0;
        if (b[x] >= K) vb.emplace_back(x);
        for (int k = 0; k < K; ++k) g[x<<lgK | k] = b[x] > (K - 1 - k)? 1 : 0;
    }

    ntt(f); ntt(g);
    for (int n = 0; n < N; ++n) f[n] *= g[n];
    ntt(f, true);

    for (int x = 0; x < 2 * MAXD; ++x) c[x] = f[x<<lgK | (K - 1)].val;
    for (int x : va) for (int y : vb) c[x + y] += min(a[x], b[y]) - K;

    pair<int, int> ans(-1, -1);
    for (int x = 0; x < 2 * MAXD; ++x) ans = max(ans, make_pair(c[x], x));
    cout << ans.first << ' ' << ans.second;
    return 0;
}
