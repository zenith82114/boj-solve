/*
 * Q11408 - MCMF
 * Date: 2022.1.31
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAX = 802, INF = INT32_MAX;

array<array<bool, MAX>, MAX> cap;
array<array<int, MAX>, MAX> cost;
array<vector<int>, MAX> adj;
array<int, MAX> dist, pred;

void addEdge(int u, int v, int w) {
    adj[u].push_back(v);
    cap[u][v] = true;
    cost[u][v] = w;
    adj[v].push_back(u);
    cap[v][u] = false;
    cost[v][u] = -w;
}

bool spfa(int S, int T) {
    queue<int> q;
    bitset<MAX> inq;
    int u;
    dist.fill(INF);
    dist[S] = 0;
    q.push(S);
    while (!q.empty()) {
        u = q.front(); q.pop();
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
    cin.tie(0)->sync_with_stdio(0);
    int N, M, T, C, F, n, m, k, c;

    cin >> N >> M;
    T = N+M+1;
    for (n = 1; n <= N; n++) {
        addEdge(0, n, 0);
        cin >> k;
        while (k--) {
            cin >> m >> c;
            addEdge(n, m+N, c);
        }
    }
    for (m = 1; m <= M; m++)
        addEdge(m+N, T, 0);

    F = C = 0;
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
