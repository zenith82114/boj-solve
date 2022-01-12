/*
 * Q1648 - Broken profile DP
 * Date: 2022.1.12
 */

#include<iostream>
#include<algorithm>
using namespace std;

const int price[6][6] = {
   {10,8,7,5,0,1},
    {8,6,4,3,0,1},
    {7,4,3,2,0,1},
    {5,3,2,2,0,1},
    {0,0,0,0,0,0},
    {1,1,1,1,0,0}
};
int label[15][15];
int dp[15][15][1<<15];

inline int getPrice(int n1, int m1, int n2, int m2) {
    return price[label[n1][m1]][label[n2][m2]];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, K, k1, k2;
    char c;

    cin >> N >> M;
    K = 1 << (M+1);
    for (int n = 1; n <= N; n++) {
        for (int m = 1; m <= M; m++) {
            cin >> c;
            label[n][m] = c - 'A';
        }
    }

    dp[0][M][0] = 0;
    for (int n = 1; n <= N; n++) {
        for (int k = 0; k < (K>>1); k++)
            dp[n][0][k<<1] = dp[n-1][M][k];
        for (int m = 1, t1 = 1, t2 = 2; m <= M; m++, t1 <<= 1, t2 <<= 1) {
            for (int k = 0; k < K; k++) {
                k1 = k & t1;
                k2 = k & t2;
                if (!k1) {
                    // case 00
                    if (!k2)
                        dp[n][m][k] = max({
                            dp[n][m-1][k], dp[n][m-1][k|t1], dp[n][m-1][k|t2]
                        });
                    // case 10
                    else if (m < M)
                        dp[n][m][k] = dp[n][m-1][k^t2] + getPrice(n, m, n, m+1);
                }
                    // case 01
                else if (!k2 && n < N)
                    dp[n][m][k] = dp[n][m-1][k^t1] + getPrice(n, m, n+1, m);
            }
        }
    }

    cout << dp[N][M][0] << '\n';
    return 0;
}
