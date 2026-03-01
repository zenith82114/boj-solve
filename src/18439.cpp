/*
 * Q18439 - bitset optimization (SWAR)
 * Date: 2026.3.1
 */

#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
constexpr int
    MAXN = 5e4,
    MAXW = (MAXN + 63) >> 6;

u64 dp[MAXW], mask[26][MAXW];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t; cin >> s >> t;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        mask[s[i] - 'A'][i >> 6] |= (1ull << (i & 63));
    }

    int nw = (n + 63) >> 6;
    for (char ct : t) {
        u64 carry = 0;
        u64 borrow = 1;
        for (int i = 0; i < nw; ++i) {
            u64 x = dp[i] | mask[ct - 'A'][i];
            u64 e = (dp[i] << 1) | carry;
            carry = dp[i] >> 63;
            u64 y = x - e - borrow;
            borrow = (x < e || (x == e && borrow));
            dp[i] = x & ~y;
        }
    }

    int ans = 0;
    for (int i = 0; i < nw; ++i) ans += __builtin_popcountll(dp[i]);
    cout << ans;
    return 0;
}
