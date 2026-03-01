/*
 * Q18440 - Hirschberg's, bitset optimization (SWAR)
 * Date: 2026.3.1
 */

#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
constexpr int
    MAXN = 5e4,
    MAXW = (MAXN + 63) >> 6;

string u;
u64 fw[MAXW], bw[MAXW], mask[26][MAXW];

template <typename T>
void toggle_masks(T begin, T end) {
    int j = 0;
    for (auto it = begin; it != end; ++it, ++j) {
        mask[*it - 'A'][j >> 6] ^= (1ull << (j & 63));
    }
}

template <typename T>
void run_dp(u64 dp[], int mw, T begin, T end) {
    fill(dp, dp + mw, 0);

    for (auto it = begin; it != end; ++it) {
        u64 carry = 0;
        u64 borrow = 1;
        for (int j = 0; j < mw; ++j) {
            u64 x = dp[j] | mask[*it - 'A'][j];
            u64 e = (dp[j] << 1) | carry;
            carry = dp[j] >> 63;
            u64 y = x - e - borrow;
            borrow = (x < e || (x == e && borrow));
            dp[j] = x & ~y;
        }
    }
}

void dnc(const string_view s, const string_view t) {
    if (s.empty() || t.empty()) return;
    if (s.size() == 1u) {
        if (t.find(s[0]) != string_view::npos) u.push_back(s[0]);
        return;
    }

    int n = s.size(), m = t.size();
    int mw = (m + 63) >> 6;

    toggle_masks(t.begin(), t.end());
    run_dp(fw, mw, s.begin(), s.begin() + n/2);
    toggle_masks(t.begin(), t.end());

    toggle_masks(t.rbegin(), t.rend());
    run_dp(bw, mw, s.rbegin(), s.rbegin() + (n - n/2));
    toggle_masks(t.rbegin(), t.rend());

    int curr = 0;
    for (int j = 0; j < mw; ++j) curr += __builtin_popcountll(bw[j]);

    int best = -1, k = -1;
    for (int j = 0; j < m; ++j) {
        if (best < curr) best = curr, k = j;
        curr += 1 & (fw[j >> 6] >> (j & 63));
        curr -= 1 & (bw[(m - 1 - j) >> 6] >> ((m - 1 - j) & 63));
    }
    if (best < curr) k = m;

    dnc(s.substr(0, n/2), t.substr(0, k));
    dnc(s.substr(n/2), t.substr(k));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t; cin >> s >> t;
    dnc(s, t);
    cout << u.size() << '\n' << u;
    return 0;
}
