/*
 * Q13974 - Knuth's optimization
 * Date: 2022.2.18
 */

#include<bits/stdc++.h>
using namespace std;

ulong S[5001], dp[5001][5001];
int opt[5001][5001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int N; cin >> N;

        S[0] = 0;
        for (int i = 1; i <= N; ++i) {
            cin >> S[i];
            S[i] += S[i-1];
        }
        for (int i = 1; i < N; ++i) {
            dp[i][i+1] = S[i+1] - S[i-1];
            opt[i][i+1] = i;
        }
        for (int d = 2; d < N; ++d) {
            for (int i = 1, j = i+d; j <= N; ++i, ++j) {
                ulong mf = ULONG_MAX;
                int mk = 0;
                for (int k = opt[i][j-1]; k <= opt[i+1][j]; ++k) {
                    ulong f = dp[i][k] + dp[k+1][j];
                    if (mf > f)
                        mf = f, mk = k;
                }
                mf += S[j] - S[i-1];
                dp[i][j] = mf;
                opt[i][j] = mk;
            }
        }
        cout << dp[1][N] << '\n';
    }

    return 0;
}
