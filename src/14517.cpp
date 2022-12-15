/*
 * Q14517 - DP
 * Date: 2022.9.15
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    const int MOD = 10'007;

    string s; cin >> s;
    const int N = s.size();

    int dp[1000], dp_i[1000];
    memset(dp, 0, N * sizeof(int));

    for (int i = N-1; ~i; --i) {
        dp_i[i] = 1;
        int psum = 0;
        for (int j = i+1; j < N; ++j) {
            dp_i[j] = s[i] == s[j]? psum + 1 : 0;
            psum += dp[j];
        }
        for (int j = i; j < N; ++j)
            dp[j] = (dp[j] + dp_i[j]) % MOD;
    }

    int ans = 0;
    for (int j = 0; j < N; ++j)
        ans += dp[j];
    cout << ans % MOD << '\n';
    return 0;
}
