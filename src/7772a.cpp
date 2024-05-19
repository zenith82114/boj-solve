/*
 * Q7772a - DP + combinatorics
 * Date: 2024.5.19
 */

#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u64 dp[5][51] {};
    dp[0][0] = 1;

    // combination with repetition
    auto cwr = [] (u64 x, int y) -> u64 {
        u64 ans = 1;
        for (int i = 0; i < y; ++i) {
            ans *= x + i;
            ans /= i + 1;
        }
        return ans;
    };

    int n; cin >> n;

    for (int m = 1; m <= (n-1)/2; ++m) {
        u64 g = 0;
        for (int i = 0; i < 4; ++i) g += dp[i][m-1];

        for (int i = 4; i > 0; --i)
        for (int j = n; j >= m; --j)
        for (int c = 1; c <= i; ++c) {
            int k = j - c*m;
            if (k >= 0) dp[i][j] += cwr(g, c) * dp[i-c][k];
        }
    }

    u64 ans = 0;
    for (int i = 0; i < 5; ++i) ans += dp[i][n-1];
    if (~n&1) {
        u64 g = 0;
        for (int i = 0; i < 4; ++i) g += dp[i][n/2-1];
        ans += g*(g+1)/2;
    }
    cout << ans;
    return 0;
}
