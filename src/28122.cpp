/*
 * Q28122 - trie, dp
 * Date: 2025.6.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

constexpr int MAXN = 2 + 12e6;
int g[MAXN][2] {}, s[MAXN] {};

int dp(int x, int t) {
    if (s[x] == t) return 0;
    int l = g[x][0], r = g[x][1];
    if (l && r) return 1 + max(
        dp(l, 1 + max(0, t - s[r])),
        dp(r, 1 + max(0, t - s[l]))
    );
    if (l || r) return 1 + dp(l ? l : r, 1 + t);
    return s[x] - t;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int m = 1;
    while (n--) {
        i64 a; cin >> a;
        int x = 1; ++s[x];
        for (int i = 0; i < 60; ++i) {
            int b = a & 1;
            if (!g[x][b]) g[x][b] = ++m;
            x = g[x][b]; ++s[x];
            a >>= 1;
        }
    }
    cout << dp(1, 0);
    return 0;
}
