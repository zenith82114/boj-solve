/*
 * Q1031 - Maximum flow
 * Date: 2023.4.2
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int cap[128][128];
    vector<int> adj[128];
    int pred[128];

    memset(cap, 0, sizeof cap);
    int N, M; cin >> N >> M;
    const int S = N + M;
    const int T = S + 1;

    const auto add_edge = [&] (int u, int v, int c) {
        cap[u][v] = c;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    };

    int C1 = 0;
    for (int i = 0; i < N; ++i) {
        int c; cin >> c;
        C1 += c;
        add_edge(S, i, c);
    }
    int C2 = 0;
    for (int j = 0; j < M; ++j) {
        int c; cin >> c;
        C2 += c;
        add_edge(N + j, T, c);
    }
    if (C1 != C2) { cout << -1; return 0; }
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
        add_edge(i, N + j, 1);

    const auto bfs1 = [&] (int s, int t) {
        queue<int> q; q.emplace(s);
        memset(pred, -1, sizeof pred);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const int& v : adj[u]) if (!~pred[v] && cap[u][v]) {
                pred[v] = u;
                if (v == t) return true;
                q.emplace(v);
            }
        }
        return false;
    };
    int F = 0;
    while (bfs1(S, T)) {
        ++F;
        for (int v = T; v != S; v = pred[v])
            --cap[pred[v]][v], ++cap[v][pred[v]];
    }
    if (F != C1) { cout << -1; return 0; }

    const auto bfs2 = [&] (int s, int t) {
        queue<int> q; q.emplace(s);
        memset(pred, -1, sizeof pred);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const int& v : adj[u]) if (!~pred[v] && cap[u][v]) {
                if (make_pair(u, v) < make_pair(s, t)) continue;
                pred[v] = u;
                if (v == t) return true;
                q.emplace(v);
            }
        }
        return false;
    };

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) if (!cap[i][N + j] && bfs2(i, N + j)) {
        ++cap[i][N + j];
        for (int v = N + j; v != i; v = pred[v])
            --cap[pred[v]][v], ++cap[v][pred[v]];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) cout << (cap[i][N + j] ^ 1);
        cout << '\n';
    }

    return 0;
}
