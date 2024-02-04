/*
 * Q1129 - DP + greedy
 * Date: 2024.2.4
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int x[64];
    int dp[64][64];

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    sort(x+1, x+n+1);

    dp[2][3] = x[3] - x[1];
    for (int j = 4; j <= n; ++j) {
        dp[2][j] = max(dp[2][j-1], x[j] - x[j-1]);
    }
    for (int i = 3; i < n; ++i) {
        dp[i][i+1] = INT32_MAX;
        for (int k = 2; k < i; ++k) {
            dp[i][i+1] = min(dp[i][i+1], max(dp[k][i], x[i+1] - x[k]));
        }
        for (int j = i+2; j <= n; ++j) {
            dp[i][j] = max(dp[i][j-1], x[j] - x[j-1]);
        }
    }

    int D = INT32_MAX;
    for (int s = 2; s < n; ++s) {
        D = min(D, max(dp[s][n], x[n] - x[s]));
    }

    vector<int> v1, v2;
    int e = x[1];
    for (int i = 1; i <= n; ++i) {
        if (x[i] > e + D) {
            v2.emplace_back(v1.back());
            v1.pop_back();
            e = v2.back();
        }
        v1.emplace_back(x[i]);
    }
    reverse(v2.begin(), v2.end());
    for (int y : v1) cout << y << ' ';
    for (int y : v2) cout << y << ' ';
    return 0;
}
