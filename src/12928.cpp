/*
 * Q12928 - DP
 * Date: 2022.10.4
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    char dp[51][101][1001];
    memset(dp, 0, sizeof dp);

    int N, S; cin >> N >> S;

    dp[1][1][0] = 1;
    for (int n = 1; n < N; ++n)
    for (int d = 0; d <= 2*(N-1); ++d)
    for (int s = 0; s <= S; ++s)
    if (dp[n][d][s]) {
        for (int i = 1; d + i <= 2*(N-1); ++i) {
            int iC2 = (i * (i-1))/2;
            if (s + iC2 > S) break;
            dp[n + 1][d + i][s + iC2] = 1;
        }
    }

    cout << (int)dp[N][2*(N-1)][S] << '\n';
    return 0;
}
