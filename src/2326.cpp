/*
 * Q2326 - DP
 * Date: 2023.9.11
 */

#include<iostream>
#include<string>
using namespace std;

int dp[1001][1001] {};
int memo[128] {};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    string x, y; cin >> x >> y;
    int n = x.size(); x.insert(x.begin(), '$');
    int m = y.size(); y.insert(y.begin(), '$');

    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        dp[i][0] = i;
        int xi = x[i];
        int sj = 0;
        for (int j = 1; j <= m; ++j) {
            int yj = y[j];
            int si = memo[yj];
            int& ans = dp[i][j] = max(n, m);
            ans = min(ans, dp[i-1][j] + 1);
            ans = min(ans, dp[i][j-1] + 1);
            ans = min(ans, dp[i-1][j-1] + (xi == yj? 0 : 1));
            if (si && sj)
                ans = min(ans, dp[si-1][sj-1] + (i - si) + (j - sj) - 1);
            if (xi == yj) sj = j;
        }
        memo[xi] = i;
    }

    cout << dp[n][m];
    return 0;
}
