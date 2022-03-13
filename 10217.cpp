/*
 * Q10217 - Dijkstra's + DP
 * Date: 2021.7.22, 2022.3.13(revised)
 */

#include<iostream>
#include<array>
#include<vector>
#include<queue>
using namespace std;
constexpr int INF = INT32_MAX;

struct Info { int v, c, d; };
struct cmpInfo {
    bool operator()(const Info& lhs, const Info& rhs) const {
        return lhs.d > rhs.d;
    }
};
array<vector<Info>, 101> adj;
array<array<int, 10001>, 101> dp;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int TC;
    int N, M, K, u, v, c, d, r;
    int c_new, d_new;

    cin >> TC;
    while (TC--) {
        cin >> N >> M >> K;
        for (v = 1; v <= N; v++)
            adj[v].clear();
        while (K--) {
            cin >> u >> v >> c >> d;
            adj[u].push_back({v, c, d});
        }

        for (c = 0; c <= M; c++)
            dp[1][c] = 0;
        for (v = 1; v <= N; v++) {
            for (c = 0; c <= M; c++)
                dp[v][c] = INF;
        }

        priority_queue<Info, vector<Info>, cmpInfo> pq;
        pq.push({1, 0, 0});
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            if (dp[cur.v][cur.c] < cur.d)
                continue;
            for (auto& nxt : adj[cur.v]) {
                c_new = cur.c + nxt.c;
                d_new = cur.d + nxt.d;
                for (c = c_new; c <= M && dp[nxt.v][c] > d_new; c++)
                    dp[nxt.v][c] = d_new;
                if (c > c_new)
                    pq.push({nxt.v, c_new, d_new});
            }
        }
        r = dp[N][M];
        if (r == INF) cout << "Poor KCM\n";
        else cout << r << '\n';
    }

    return 0;
}
