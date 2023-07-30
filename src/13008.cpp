/*
 * Q13008 - Dijkstra's alg. + DP
 * Date: 2023.7.31
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int inf = INT32_MAX>>1;

vector<pair<int, int> > adj[51];
priority_queue<pair<int, int> > pq;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, C; cin >> N >> M >> C;
    while (M--) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
    }

    vector<int> dp0(N+1), dp1(N+1, inf); dp1[1] = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        auto [d, x] = pq.top(); pq.pop(); d = -d;
        if (dp1[x] < d) continue;
        for (const auto& [y, w] : adj[x]) if (dp1[y] > dp1[x] + w) {
            dp1[y] = dp1[x] + w;
            pq.emplace(-dp1[y], y);
        }
    }

    int ans = dp1[N];

    for (int c = 0; c < C; ++c) {
        dp0.swap(dp1);
        fill(dp1.begin(), dp1.end(), inf);

        for (int x = 1; x <= N; ++x) if (dp0[x] != inf) {
            for (const auto& [y, w] : adj[x])
                dp1[y] = min(dp1[y], dp0[x] - w);
        }

        for (int x = 1; x <= N; ++x) pq.emplace(-dp1[x], x);
        while (!pq.empty()) {
            auto [d, x] = pq.top(); pq.pop(); d = -d;
            if (dp1[x] < d) continue;
            for (const auto& [y, w] : adj[x]) if (dp1[y] > dp1[x] + w) {
                dp1[y] = dp1[x] + w;
                pq.emplace(-dp1[y], y);
            }
        }

        ans = min(ans, dp1[N]);
    }

    cout << ans;
    return 0;
}
