/*
 * Q10217 - DP
 * Date: 2023.6.18
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    constexpr int inf = INT32_MAX>>1;
    using iiii = tuple<int, int, int, int>;

    int N, M, K; cin >> N >> N >> M >> K;
    vector<iiii> edges;
    while (K--) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        edges.emplace_back(--u, --v, c, d);
    }

    vector<vector<int> > dp(M+1, vector<int>(N, inf));

    for (int m = 0; m <= M; ++m) {
        dp[m][0] = 0;
        for (const auto& [u, v, c, d] : edges) if (c <= m)
            dp[m][v] = min(dp[m][v], dp[m - c][u] + d);
    }

    int ans = inf;
    for (int m = 0; m <= M; ++m) ans = min(ans, dp[m][N-1]);
    if (ans < inf) cout << ans; else cout << "Poor KCM";
    return 0;
}
