/*
 * Q2316 - Vertex-disjoint paths as network flow
 * Date: 2022.1.27
 */

#include<iostream>
#include<array>
#include<queue>
using namespace std;

array<array<int, 802>, 802> cap;
array<bool, 802> visited;
array<int, 802> pred;
int N;

constexpr int IN(int v) { return v<<1; }
constexpr int OUT(int v) { return (v<<1)|1; }

bool bfs(int S, int T) {
    queue<int> q;
    int u, v;
    q.push(S);
    visited.fill(false);
    visited[S] = true;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (v = IN(1); v <= OUT(N); v++) {
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int P, u, v, C;

    cin >> N >> P;
    for (v = 1; v <= N; v++)
        cap[IN(v)][OUT(v)] = 1;
    while (P--) {
        cin >> u >> v;
        cap[OUT(u)][IN(v)] = 1;
        cap[OUT(v)][IN(u)] = 1;
    }

    C = 0;
    while (bfs(OUT(1), IN(2))) {
        C++;
        for (v = IN(2); v != OUT(1); v = pred[v]) {
            cap[pred[v]][v]--;
            cap[v][pred[v]]++;
        }
    }

    cout << C << '\n';
    return 0;
}
