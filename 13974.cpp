/*
 * Q13974 - Knuth's optimization
 * Date: 2022.2.18
 */

#include<bits/stdc++.h>
using namespace std;

ulong S[5001], dp[5001][5001];
int opt[5001][5001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TC, N;
    ulong f, mf, mk;

    cin >> TC;
    while (TC--) {
        cin >> N;

        S[0] = 0;
        for (int i=1; i<=N; i++) {
            cin >> S[i];
            S[i] += S[i-1];
        }
        for (int i=1; i<N; i++) {
            dp[i][i+1] = S[i+1] - S[i-1];
            opt[i][i+1] = i;
        }
        for (int d=2; d<N; d++) {
            for (int i=1, j=i+d; j<=N; i++, j++) {
                mf = ULONG_MAX;
                for (int k=opt[i][j-1]; k<=opt[i+1][j]; k++) {
                    f = dp[i][k] + dp[k+1][j];
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
