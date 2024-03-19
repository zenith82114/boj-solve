/*
 * Q12106 - KMP + DP
 * Date: 2024.3.19
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    constexpr int MOD = 1e9+9;
    int ff[100];
    int dp[100][100];
    int n; cin >> n;
    string S; cin >> S;
    int m = S.size();

    ff[0] = 0;
    for (int j = 0, i = 1; i < m; ++i) {
        while (j > 0 && S[j] != S[i]) j = ff[j-1];
        if (S[i] == S[j]) ++j;
        ff[i] = j;
    }

    for (int i = 0; i < n; ++i) memset(dp[i], 0, m * sizeof(int));
    dp[0][0] = 25;
    dp[0][1] = 1;

    for (int i = 1; i < n; ++i)
    for (int j = 0; j < m; ++j)
    for (char c = 'a'; c <= 'z'; ++c) {
        int nj = j;
        while (nj > 0 && S[nj] != c) nj = ff[nj-1];
        if (S[nj] == c) ++nj;
        dp[i][nj] = (dp[i][nj] + dp[i-1][j]) % MOD;
    }

    int ans = 1;
    for (int i = 0; i < n; ++i) ans = (ans * 26ll) % MOD;
    for (int j = 0; j < m; ++j) ans = (ans + MOD - dp[n-1][j]) % MOD;
    cout << ans;
    return 0;
}
