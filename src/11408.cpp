/*
 * Q11408 - min cost flow
 * Date: 2022.1.31
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAX = 802, INF = INT32_MAX;

array<array<bool, MAX>, MAX> cap;
array<array<int, MAX>, MAX> cost;
array<vector<int>, MAX> adj;
array<int, MAX> dist, pred;

void add_edge(int u, int v, int w) {
    adj[u].push_back(v);
    cap[u][v] = true;
    cost[u][v] = w;
    adj[v].push_back(u);
    cap[v][u] = false;
    cost[v][u] = -w;
}

bool spfa(int S, int T) {
    queue<int> q; q.push(S);
    dist.fill(INF); dist[S] = 0;
    bitset<MAX> inq;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq.reset(u);
        for (int& v : adj[u]) {
            if (cap[u][v] && dist[v] > dist[u] + cost[u][v]) {
                dist[v] = dist[u] + cost[u][v];
                pred[v] = u;
                if (!inq.test(v)) {
                    q.push(v);
                    inq.set(v);
                }
            }
        }
    }
    return dist[T] != INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    int T = N+M+1;
    for (int n = 1; n <= N; ++n) {
        add_edge(0, n, 0);
        int k; cin >> k;
        while (k--) {
            int m, c; cin >> m >> c;
            add_edge(n, m+N, c);
        }
    }
    for (int m = 1; m <= M; ++m)
        add_edge(m+N, T, 0);

    int F = 0, C = 0;
    while (spfa(0, T)) {
        for (int v = T; v != 0; v = pred[v]) {
            C += cost[pred[v]][v];
            cap[pred[v]][v] = false;
            cap[v][pred[v]] = true;
        }
        F++;
    }

    cout << F << '\n' << C << '\n';
    return 0;
}
