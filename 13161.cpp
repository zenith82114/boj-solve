/*
 * Q13161 - MCMF duality and Dinic's alg.
 * Date: 2022.1.28
 */

#include<iostream>
#include<array>
#include<vector>
#include<queue>
using namespace std;
constexpr int INF = INT32_MAX;

array<array<int, 512>, 512> cap;
array<vector<int>, 512> adj;
array<int, 512> party, level, adjLen, hist;
int S, T;

bool bfs() {
    queue<int> q;
    int u;
    q.push(S);
    for (u = 1; u <= T; u++)
        level[u] = -1;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (int& v : adj[u]) {
            if (cap[u][v] > 0 && level[v] < 0) {
                level[v] = level[u]+1;
                q.push(v);
            }
        }
    }
    return level[T] != -1;
}

int dfs(int u, int f) {
    int v, r;
    if (u == T)
        return f;
    for (int& i = hist[u]; i < adjLen[u]; i++) {
        v = adj[u][i];
        if (cap[u][v] > 0 && level[v] == level[u]+1) {
            if ((r = dfs(v, min(f, cap[u][v]))) > 0) {
                cap[u][v] -= r;
                cap[v][u] += r;
                return r;
            }
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, u, v, f, F;

    cin >> N;
    S = 0, T = N+1;
    for (u = 1; u <= N; u++) {
        cin >> party[u];
        if (party[u] == 1) {
            cap[S][u] = INF;
            adj[S].push_back(u);
            adj[u].push_back(S);
        }
        if (party[u] == 2) {
            cap[u][T] = INF;
            adj[u].push_back(T);
            adj[T].push_back(u);
        }
    }
    for (u = 1; u <= N; u++) {
        for (v = 1; v <= N; v++) {
            cin >> cap[u][v];
            if (party[u] == 2 || party[v] == 1)
                cap[u][v] = 0;
            if (u != v)
                adj[u].push_back(v);
        }
    }
    for (u = S; u <= T; u++)
        adjLen[u] = adj[u].size();

    F = 0;
    level[S] = 0;
    while (bfs()) {
        for (u = S; u <= T; u++)
            hist[u] = 0;
        while ((f = dfs(S, INF)) > 0)
            F += f;
    }

    cout << F << '\n';
    for (u = 1; u <= N; u++)
        if (level[u] != -1)
            cout << u << ' ';
    cout << '\n';
    for (u = 1; u <= N; u++)
        if (level[u] == -1)
            cout << u << ' ';
    cout << '\n';
    return 0;
}
