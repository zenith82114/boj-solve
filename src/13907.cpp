/*
 * Q13907 - DP
 * Date: 2025.9.3
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int inf = 0x3f3f3f3f;

vector<tuple<int, int, int> > edg;
vector<pair<int, int> > opt;
int dp[2][1004] {};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    int s, d; cin >> s >> d;
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        edg.emplace_back(x, y, w);
        edg.emplace_back(y, x, w);
    }

    memset(dp[1], inf, sizeof dp[0]);
    dp[1][s] = 0;
    for (int i = 1; i < n; ++i) {
        memcpy(dp[0], dp[1], sizeof dp[0]);
        for (const auto& [x, y, w] : edg) {
            dp[1][y] = min(dp[1][y], dp[0][x] + w);
        }
        if (dp[0][d] > dp[1][d]) opt.emplace_back(dp[1][d], i);
    }

    cout << opt.back().first << '\n';
    int p_acc = 0;
    while (k--) {
        int p; cin >> p;
        p_acc += p;
        int ans = inf;
        for (const auto& [d0, i] : opt) ans = min(ans, d0 + i*p_acc);
        cout << ans << '\n';
    }

    return 0;
}
