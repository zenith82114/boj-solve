/*
 * Q7981 - Graph DP (Dijkstra's)
 * Date: 2022.10.5
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;

vector<vector<int> > adj, adj_rev;
vector<i64> dp, dp_u;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    adj.resize(N+1);
    adj_rev.resize(N+1);
    dp_u.resize(N+1);
    dp.resize(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> dp_u[i] >> dp[i];
        int r; cin >> r;
        adj[i].resize(r);
        for (int &j : adj[i]) {
            cin >> j;
            adj_rev[j].emplace_back(i);
        }
    }
    for (int i = 1; i <= N; ++i)
        for (const int &j : adj[i])
            dp_u[i] += dp[j];

    using pli = pair<i64, int>;
    priority_queue<pli, vector<pli>, greater<pli> > pq;
    for (int i = 1; i <= N; ++i)
        if (dp_u[i] < dp[i])
            pq.emplace(dp_u[i], i);

    while (!pq.empty()) {
        int i = pq.top().second; pq.pop();
        if (dp[i] > dp_u[i]) {
            i64 x = dp[i] - dp_u[i];
            dp[i] = dp_u[i];
            for (const int &j : adj_rev[i]) {
                dp_u[j] -= x;
                if (dp[j] > dp_u[j])
                    pq.emplace(dp_u[j], j);
            }
        }
    }

    cout << dp[1] << '\n';
    return 0;
}
