/*
 * Q1648 - Broken profile DP
 * Date: 2022.1.12
 */

#include<iostream>
using namespace std;

int dp[15][15][1<<15];

inline void addMod(int& a, const int b) {
    a = (a + b) % 9901;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, K, v, k1, k2;

    cin >> N >> M;
    if (N & M & 1)
        cout << 0 << '\n';
    else {
        if (N < M)
            swap(N, M);
        K = 1 << (M+1);

        dp[0][M][0] = 1;
        for (int n = 1; n <= N; n++) {
            for (int k = 0; k < (K>>1); k++)
                dp[n][0][k<<1] = dp[n-1][M][k];
            for (int m = 0, t1 = 1, t2 = 2; m < M; m++, t1 <<= 1, t2 <<= 1) {
                for (int k = 0; k < K; k++) {
                    if ((v = dp[n][m][k]) != 0) {
                        k1 = k & t1;
                        k2 = k & t2;
                        if (!k1 && !k2) {
                            addMod(dp[n][m+1][k | t1], v);
                            addMod(dp[n][m+1][k | t2], v);
                        }
                        else if (!k1 != !k2)
                            addMod(dp[n][m+1][k ^ k1 ^ k2], v);
                    }
                }
            }
        }
        cout << dp[N][M][0] << '\n';
    }

    return 0;
}
