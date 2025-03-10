/*
 * Q2401 - KMP, DP
 * Date: 2025.3.10
 */

#include<bits/stdc++.h>
using namespace std;

string P[500];
int B[500][10004] {};
int J[500] {};
int dp[100004] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string T; cin >> T;
    int n = T.size();
    int k; cin >> k;
    for (int x = 0; x < k; ++x) {
        auto& p = P[x];
        cin >> p;
        int m = p.size();
        auto& b = B[x];
        for (int i = 1, j = 0; i < m; ++i) {
            while (j && p[i] != p[j]) j = b[j - 1];
            if (p[i] == p[j]) ++j;
            b[i] = j;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < k; ++x) {
            auto& p = P[x];
            auto& b = B[x];
            auto& j = J[x];
            int m = p.size();
            while (j && T[i] != p[j]) j = b[j - 1];
            if (T[i] == p[j]) ++j;
            if (j == m) {
                dp[i] = max(dp[i], (i >= m? dp[i - m] : 0) + m);
                j = b[j - 1];
            }
        }
        dp[i + 1] = dp[i];
    }

    cout << dp[n - 1];
    return 0;
}
