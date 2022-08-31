/*
 * Q13907 - Graph DP
 * Date: 2022.8.31
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    constexpr int inf = INT_MAX;

    int N, M, K; cin >> N >> M >> K;
    int S, D; cin >> S >> D;

    vector<vector<pair<int, int> > > graph(N +1);
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    vector<int> dp0(N +1);
    vector<int> dp1(N +1, inf);
    dp1[S] = 0;
    vector<bool> upd0(N +1);
    vector<bool> upd1(N +1, false);
    upd1[S] = true;

    vector<pair<int, int> > opt;

    for (int k = 1; k < N; ++k) {
        copy(dp1.begin(), dp1.end(), dp0.begin());
        upd0.swap(upd1);
        fill(upd1.begin(), upd1.end(), false);
        for (int u = 1; u <= N; ++u) if (upd0[u]) {
            for (const auto &e : graph[u]) {
                int v, w; tie(v, w) = e;
                if (dp1[v] > dp0[u] + w) {
                    dp1[v] = dp0[u] + w;
                    upd1[v] = true;
                }
            }
        }
        if (dp0[D] > dp1[D])
            opt.emplace_back(k, dp1[D]);
    }

    cout << opt.back().second << '\n';

    int P = 0;
    while (K--) {
        int p; cin >> p;
        P += p;
        int ans = inf;
        for (const auto &o : opt)
            ans = min(ans, o.first * P + o.second);
        cout << ans << '\n';
    }

    return 0;
}
