/*
 * Q15491 - tree DP
 * Date: 2025.2.16
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1'000'001;

vector<int> g[MAXN];
int a[MAXN], par[MAXN], dp[MAXN][2] {};

void dfs0(int px, int x) {
    dp[x][0] = a[x];
    par[x] = px;
    for (int y : g[x]) if (y != px) {
        dfs0(x, y);
        dp[x][0] = max(dp[x][0], dp[y][0]);
    }
}

void dfs1(int x) {
    int m1 = 0, m2 = 0;
    for (int y : g[x]) if (y != par[x]) {
        if (m1 <= dp[y][0]) m2 = m1, m1 = dp[y][0];
        else m2 = max(m2, dp[y][0]);
    }
    for (int y : g[x]) if (y != par[x]) {
        dp[y][1] = max({ a[x], dp[x][1], (dp[y][0] < m1? m1 : m2) });
        dfs1(y);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int e = n - 1; e--;) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dfs0(0, 1);
    dfs1(1);

    int ans = 0;
    for (int x = 1; x <= n; ++x) {
        int ansx = dp[x][1];
        for (int y : g[x]) if (y != par[x]) ansx += dp[y][0];
        ans = max(ans, ansx);
    }
    cout << ans;
    return 0;
}
