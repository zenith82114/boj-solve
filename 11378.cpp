/*
 * Q11378 - Advanced bipartite matching as network flow
 * Date: 2022.1.26
 */

#include<iostream>
#include<array>
#include<queue>
using namespace std;

array<array<int, 2003>, 2003> G{};
array<bool, 2003> visited;
array<int, 2003> pred;

bool bfs(int S, int T) {
    queue<int> q;
    int u, v;
    q.push(S);
    visited.fill(false);
    visited[S] = true;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (v = 0; v <= T; v++) {
            if (!visited[v] && G[u][v] > 0) {
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, K, T, l, n, m, C;

    cin >> N >> M >> K;
    T = N+M+2;
    G[0][T-1] = K;
    for (n = 1; n <= N; n++) {
        G[0][n] = 1;
        G[T-1][n] = K;
        cin >> l;
        while (l--) {
            cin >> m;
            G[n][m+N] = 1;
        }
    }
    for (m = 1; m <= M; m++)
        G[m+N][T] = 1;

    C = 0;
    while (bfs(0, T)) {
        C++;
        for (int v = T; v != 0; v = pred[v]) {
            G[pred[v]][v]--;
            G[v][pred[v]]++;
        }
    }

    cout << C << '\n';
    return 0;
}
