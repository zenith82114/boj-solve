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

inline int IN(int v) { return v<<1; }
inline int OUT(int v) { return (v<<1)|1; }

bool bfs(const int N, const int S, const int T) {
    queue<int> q;
    q.push(S);
    visited.fill(false);
    visited[S] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = IN(1); v <= OUT(N); v++) {
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, P; cin >> N >> P;
    for (int v = 1; v <= N; ++v)
        cap[IN(v)][OUT(v)] = 1;
    while (P--) {
        int u, v; cin >> u >> v;
        cap[OUT(u)][IN(v)] = 1;
        cap[OUT(v)][IN(u)] = 1;
    }

    int C = 0;
    while (bfs(N, OUT(1), IN(2))) {
        C++;
        for (int v = IN(2); v != OUT(1); v = pred[v]) {
            cap[pred[v]][v]--;
            cap[v][pred[v]]++;
        }
    }

    cout << C << '\n';
    return 0;
}
