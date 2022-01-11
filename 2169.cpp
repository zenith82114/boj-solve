/*
 * Q2169 - DP
 * Date: 2022.1.8
 */

#include<iostream>
#include<array>
using namespace std;

array< array<char, 1001>, 1001> val;
array< array<int, 1001>, 1001> dp;
array<int, 1001> temp1, temp2;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, v;

    cin >> N >> M;
    for (int n = 1; n <= N; n++) {
        for (int m = 1; m <= M; m++) {
            cin >> v;
            val[n][m] = (char)v;
        }
    }

    dp[N][M] = val[N][M];
    for (int m = M-1; m > 0; m--)
        dp[N][m] = val[N][m] + dp[N][m+1];
    for (int n = N-1; n > 0; n--) {
        // Case 1: moving to the left is not allowed
        temp1[M] = val[n][M] + dp[n+1][M];
        for (int m = M-1; m > 0; m--)
            temp1[m] = val[n][m] + max(dp[n+1][m], temp1[m+1]);
        // Case 2: moving to the right is not allowed
        temp2[1] = val[n][1] + dp[n+1][1];
        for (int m = 2; m <= M; m++)
            temp2[m] = val[n][m] + max(dp[n+1][m], temp2[m-1]);
        // Take max for each cell
        for (int m = 1; m <= M; m++)
            dp[n][m] = max(temp1[m], temp2[m]);
    }

    cout << dp[1][1] << '\n';
    return 0;
}
