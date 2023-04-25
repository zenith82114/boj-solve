/*
 * Q18193 - Graph compression by segment trees
 * Date: 2023.4.25
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;
    int V = 1; while (V <= N) V <<= 1;

    vector<vector<pair<int, int> > > adj(4*V + M);

    for (int i = 1; i < V; ++i) {
        adj[i].emplace_back(2*i,     0);
        adj[i].emplace_back(2*i + 1, 0);
    }
    for (int i = 1; i <= N; ++i)
        adj[V + i].emplace_back(3*V + i, 0);
    for (int i = 1; i < V; ++i) {
        adj[2*V + 2*i    ].emplace_back(2*V + i, 0);
        adj[2*V + 2*i + 1].emplace_back(2*V + i, 0);
    }

    for (int j = 0; j < M; ++j) {
        int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
        vector<int> s;
        for (b |= V, c |= V; b <= c; b >>= 1, c >>= 1) {
            if ( b&1) s.emplace_back(2*V + (b++));
            if (~c&1) s.emplace_back(2*V + (c--));
        }
        for (int u : s) adj[u].emplace_back(4*V + j, a);
        s.clear();
        for (d |= V, e |= V; d <= e; d >>= 1, e >>= 1) {
            if ( d&1) s.emplace_back(d++);
            if (~e&1) s.emplace_back(e--);
        }
        for (int u : s) adj[4*V + j].emplace_back(u, 0);
    }

    using i64 = int64_t;
    constexpr i64 inf = INT64_MAX;

    vector<i64> dist(4*V + M, inf); dist[3*V + K] = 0;
    priority_queue<pair<i64, int> > pq; pq.emplace(0, 3*V + K);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop(); d = -d;
        for (auto& [v, w] : adj[u]) if (dist[v] > d + w) {
            dist[v] = d + w;
            pq.emplace(-dist[v], v);
        }
    }

    for (int u = 3*V + 1; u <= 3*V + N; ++u)
        cout << (dist[u] != inf? dist[u] : -1) << ' ';
    return 0;
}
