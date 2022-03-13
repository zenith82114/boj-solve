/*
 * Q2098 - TSP by bitmask DP
 * Date: 2021.8.12
 */

#include<iostream>
#include<algorithm>
#include<limits>
using namespace std;
constexpr int MAX = 16;
constexpr int INF = numeric_limits<int>::max();

int W[MAX][MAX], dp[1 << MAX][MAX];

// dp[S][t] = min path that passes through nodes S and ends at node t

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, i, j, I, J;

    cin >> N; M = 1 << N;
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            cin >> W[i][j];

    for (I = 0; I < M; ++I)
        fill_n(dp[I], N, INF);
    dp[0][0] = 0;
    for (I = 0; I < M - 1; ++I)
        for (i = 0; i < N; ++i) {
            if (dp[I][i] == INF) continue;
            for (J = 1, j = 0; j < N; J <<= 1, ++j)
                if (!(I & J) && W[i][j])
                    dp[I | J][j] = min(dp[I | J][j], dp[I][i] + W[i][j]);
        }
    cout << dp[M - 1][0] << '\n';

    return 0;
}
