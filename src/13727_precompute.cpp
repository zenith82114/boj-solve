/*
 * Q13727_precompute - Bitmask DP
 * Date: 2023.1.29
 */

#include<bits/stdc++.h>
using namespace std;

array<vector<int>, 16> adj;
array<vector<int>, 65536> trans;

void backtrack(vector<int>& v, int k, int i) {
    v.emplace_back(k);

    for (; i < 16; ++i) {
        if (k & (1<<i)) continue;
        for (const int& j : adj[i]) {
            if (k & (1<<j)) continue;
            backtrack(v, k | (1<<i) | (1<<j), i+1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    for (int i = 0; i < 16; ++i) {
        if (~i&1) adj[i].emplace_back(i|1);
        if (~i&2) adj[i].emplace_back(i|2);
        if (~i&4) adj[i].emplace_back(i|4);
        if (~i&8) adj[i].emplace_back(i|8);
    }

    for (int k = 0; k < 65536; ++k)
        backtrack(trans[k], k, 0);

    array<int, 65536> dp0, dp1;
    dp1.fill(0);
    dp1[65535] = 1;

    constexpr int N_TERMS = 150;

    cout << 1;
    for (int n = 1; n < N_TERMS; ++n) {
        dp0.swap(dp1);
        dp1.fill(0);

        for (int k = 0; k < 1<<16; ++k)
            for (const int& nk : trans[k ^ 65535])
                dp1[nk] = (dp1[nk] + dp0[k]) % 1'000'000'007;

        cout << ", " << dp1[65535];
    }

    return 0;
}
