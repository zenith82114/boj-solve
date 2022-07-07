/*
 * Q11378 - Advanced bipartite matching as network flow
 * Date: 2022.1.26, 2022.7.7(revised)
 */

#include<iostream>
#include<array>
#include<queue>
using namespace std;

array<vector<int>, 2003> adj;
array<array<int, 2003>, 2003> cap;
array<bool, 2003> visited;
array<int, 2003> pred;

bool bfs(int S, int T) {
    queue<int> q;
    q.push(S);
    visited.fill(false);
    visited[S] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int& v : adj[u]) {
            if (!visited[v] && cap[u][v] > 0) {
                if (v == T) {
                    pred[T] = u;
                    return true;
                }
                visited[v] = true;
                pred[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}

#define person(i) (i+1)
#define work(i) (i+N+1)

inline void add_edge(int from, int to, int c) {
    adj[from].emplace_back(to);
    adj[to].emplace_back(from);
    cap[from][to] = c;
    cap[to][from] = 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int N, M, K; cin >> N >> M >> K;
    const int S = 0;
    const int B = 1;
    const int T = N+M+2;
    int l, m;

    add_edge(S, B, K);
    for (int n = 1; n <= N; n++) {
        add_edge(S, person(n), 1);
        add_edge(B, person(n), K);
        cin >> l;
        while (l--) {
            cin >> m;
            add_edge(person(n), work(m), 1);
        }
    }
    for (int m = 1; m <= M; m++)
        add_edge(work(m), T, 1);

    int C = 0;
    while (bfs(S, T)) {
        C++;
        for (int v = T; v != S; v = pred[v]) {
            cap[pred[v]][v]--;
            cap[v][pred[v]]++;
        }
    }

    cout << C << '\n';
    return 0;
}
