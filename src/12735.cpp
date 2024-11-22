/*
 * Q12735 - DP, combinatorics
 * Date: 2024.11.22
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    constexpr static int MOD = 1'000'000'007;
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
    mint& operator=(int v) { val = v; return *this; }

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

int l[512], r[512];
vector<int> vc { 0 };

mint binom[512][512];
mint A[512], B[512];
mint f[1024][512];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> l[i] >> r[i]; ++r[i];
        vc.emplace_back(l[i]);
        vc.emplace_back(r[i]);
    }
    sort(vc.begin(), vc.end());
    vc.erase(unique(vc.begin(), vc.end()), vc.end());

    int M = vc.size() - 2;

    for (int i = 0; i <= N; ++i) {
        binom[i][0] = 1;
        for (int j = 1; j < i; ++j) {
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
        }
        binom[i][i] = 1;
    }

    f[0][0] = 1;
    B[0] = 1;

    for (int s = 1; s <= M; ++s) {
        int Ds = vc[s + 1] - vc[s];

        for (int k = 1; k <= min(N, Ds); ++k) {
            B[k] = B[k - 1] * (Ds + 1 - k) / k;
        }

        for (int i = 0; i <= N; ++i) {
            A[i] = 0;
            for (int k = 1; k <= min(N, Ds); ++k) {
                A[i] += binom[i][k - 1] * B[k];
            }
        }

        for (int i = 0; i <= N; ++i) {
            f[s][i] = f[s - 1][i];
            if (l[i] <= vc[s] && vc[s] < r[i]) {
                int x = 0;
                for (int j = i - 1; j >= 0; --j) {
                    f[s][i] += f[s - 1][j] * A[x];
                    if (l[j] <= vc[s] && vc[s] < r[j]) ++x;
                }
            }
        }
    }

    mint ans(0);
    for (int i = 1; i <= N; ++i) ans += f[M][i];
    cout << ans;
    return 0;
}
