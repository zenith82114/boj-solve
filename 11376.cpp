/*
 * Q11376 - Bipartite matching by Edmond-Karp alg.
 * Date: 2022.1.23
 */

#include<iostream>
#include<array>
#include<queue>
using namespace std;

array<array<int, 2002>, 2002> G;
array<bool, 2002> visited;
array<int, 2002> pred;

bool bfs(int S, int T) {
    queue<int> q;
    int u, v;
    q.push(S);
    visited.fill(false);
    visited[S] = true;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (v = S; v <= T; v++) {
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
    int N, M, T, n, m, k, C;

    cin >> N >> M;
    T = N+M+1;
    for (n = 1; n <= N; n++) {
        G[0][n] = 2;
        cin >> k;
        while (k--) {
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
