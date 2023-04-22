/*
 * Q10217 - Dijkstra's + DP
 * Date: 2021.7.22
 */

#include<iostream>
#include<array>
#include<vector>
#include<queue>
using namespace std;
constexpr int INF = INT32_MAX;

struct Edge {
    int v, c, d;
    Edge(int v, int c, int d): v(v), c(c), d(d) {}
    bool operator<(const Edge& that) const {
        return d > that.d;
    }
};
array<vector<Edge>, 101> adj;
array<array<int, 10001>, 101> dp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int N, M, K; cin >> N >> M >> K;
        for (int v = 1; v <= N; ++v)
            adj[v].clear();
        while (K--) {
            int u, v, c, d;
            cin >> u >> v >> c >> d;
            adj[u].emplace_back(v, c, d);
        }

        for (int c = 0; c <= M; ++c)
            dp[1][c] = 0;
        for (int v = 1; v <= N; ++v)
        for (int c = 0; c <= M; ++c)
            dp[v][c] = INF;

        priority_queue<Edge> pq;
        pq.emplace(1, 0, 0);
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            if (dp[cur.v][cur.c] < cur.d)
                continue;
            for (auto& nxt : adj[cur.v]) {
                int c_new = cur.c + nxt.c;
                int d_new = cur.d + nxt.d;
                int c;
                for (c = c_new; c <= M && dp[nxt.v][c] > d_new; ++c)
                    dp[nxt.v][c] = d_new;
                if (c > c_new)
                    pq.emplace(nxt.v, c_new, d_new);
            }
        }

        int r = dp[N][M];
        if (r == INF) cout << "Poor KCM\n";
        else cout << r << '\n';
    }

    return 0;
}
