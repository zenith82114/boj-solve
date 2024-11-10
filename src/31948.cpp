/*
 * Q31948 - DP
 * Date: 2024.11.11
 */

#include<bits/stdc++.h>
using namespace std;

constexpr char WIN = 1, LOSE = 2;
char dp[1500][1500][3] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string S; cin >> S;
    int n = S.size();
    int qpos; for (qpos = 0; qpos < n && S[qpos] != '?'; ++qpos);

    for (int q = 0; q < 3; ++q) {
        if (qpos < n) S[qpos] = q + '0';
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && S[i] == S[j]) ++j;
            if (q == 2 && i == qpos) continue;
            for (int k = i; k < j; ++k)
            for (int l = k; l < j; ++l) dp[k][l][q] = WIN;
        }
    }

    for (int q = 0; q < 3; ++q) {
        if (qpos < n) S[qpos] = q + '0';

        /* sweep the array diagonally */
        /* losing states propagate winning states to the north and the east */
        for (int d = 0; d < n; ++d)
        for (int i = 0, j = d; j < n; ++i, ++j) {
            if (dp[i][j][q]) continue;
            dp[i][j][q] = LOSE;
            if (i - 1 >= 0 && i - 1 != qpos) {
                dp[i - 1][j][q] = WIN;
                for (int k = i - 2; k >= 0 && S[k] == S[i - 1]; --k)
                    dp[k][j][q] = WIN;
            }
            if (j + 1 < n && j + 1 != qpos) {
                dp[i][j + 1][q] = WIN;
                for (int k = j + 2; k < n && S[k] == S[j + 1]; ++k)
                    dp[i][k][q] = WIN;
            }
            if (q < 2 && i <= qpos && qpos <= j) {
                dp[i][j][2] = WIN;
            }
        }
    }

    cout << int(dp[0][n - 1][qpos < n? 2 : 0] & 1);
    return 0;
}
