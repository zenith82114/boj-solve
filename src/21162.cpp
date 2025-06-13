/*
 * Q21162 - k-th minimal string rotation; hashing, binary search
 * Date: 2025.6.13
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int p = 2e5 + 3;
constexpr int MOD = 1e9 + 7;
int b[400004], h[400004];
int ppow[200004];

bool hash_eq(int i, int j, int d) {
    int hi = (h[i + d] - h[i - 1] + MOD) % MOD;
    int hj = (h[j + d] - h[j - 1] + MOD) % MOD;
    if (i < j) hi = 1ll * hi * ppow[j - i] % MOD;
    else hj = 1ll * hj * ppow[i - j] % MOD;
    return hi == hj;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    for (int i = n; i > 0; --i) cin >> b[i];
    memcpy(b + n + 1, b + 1, n * sizeof(int));

    i64 q = 1;
    h[0] = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        h[i] = (h[i - 1] + q * b[i]) % MOD;
        q = (q * p) % MOD;
    }

    ppow[0] = 1;
    for (int i = 1; i <= n; ++i) {
        ppow[i] = (1ll * ppow[i - 1] * p) % MOD;
    }

    vector<int> idx(n - 1);
    iota(idx.begin(), idx.end(), 2);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (b[i] != b[j]) return b[i] < b[j];
        if (hash_eq(i, j, n)) return false;
        int lo = 0, hi = n - 1;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (hash_eq(i, j, mid)) lo = mid;
            else hi = mid;
        }
        return b[i + hi] < b[j + hi];
    });

    k = idx[k - 1];
    for (int i = 0; i < n; ++i) cout << b[k + i] << ' ';
    return 0;
}
