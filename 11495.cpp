/*
 * Q11495 - Maximum flow
 * Date: 2022.1.30
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAX = 2502, INF = INT32_MAX;

struct Edge { int to, cap; };
array<vector<Edge>, MAX> adj;
array<int, MAX> level, adjLen, hist;
int S, T;

bool bfs() {
    queue<int> q;
    int u;
    q.push(S);
    for (u = 0; u <= T; u++)
        level[u] = -1;
    level[S] = 0;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (auto& e : adj[u]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[u]+1;
                q.push(e.to);
            }
        }
    }
    return level[T] != -1;
}

int dfs(int u, int f) {
    int r;
    if (u == T)
        return f;
    for (int& i = hist[u]; i < adjLen[u]; i++) {
        auto& e = adj[u][i];
        if (e.cap > 0 && level[e.to] == level[u]+1) {
            if ((r = dfs(e.to, min(f, e.cap))) > 0) {
                e.cap -= r;
                for (auto& re : adj[e.to]) {
                    if (re.to == u) {
                        re.cap += r;
                        break;
                    }
                }
                return r;
            }
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int TC, N, M, C, c, F, f;

    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        S = N*M;
        T = S+1;
        adj[S].clear();
        adj[T].clear();
        C = 0;
        for (int n = 0, p = 0; n < N; n++) {
            for (int m = 0; m < M; m++, p++) {
                cin >> c;
                C += c;
                adj[p].clear();
                if ((n^m) & 1) {
                    adj[S].push_back({p, c});
                    adj[p].push_back({S, 0});
                }
                else {
                    adj[p].push_back({T, c});
                    adj[T].push_back({p, 0});
                }
                c = (n^m) & 1 ? INF : 0;
                if (n > 0)
                    adj[p].push_back({p-M, c});
                if (n < N-1)
                    adj[p].push_back({p+M, c});
                if (m > 0)
                    adj[p].push_back({p-1, c});
                if (m < M-1)
                    adj[p].push_back({p+1, c});
            }
        }
        for (int p = 0; p <= T; p++)
            adjLen[p] = adj[p].size();

        F = 0;
        while (bfs()) {
            for (int p = 0; p <= T; p++)
                hist[p] = 0;
            while ((f = dfs(S, INF)) > 0)
                F += f;
        }
        cout << C-F << '\n';
    }

    return 0;
}
