/*
 * Q1210 - Max-flow min-cut duality
 * Date: 2022.4.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int INF = INT_MAX;
const int MAX = 402;

array<array<int, MAX>, MAX> cap;
array<bool, MAX> visited;
array<int, MAX> pred;
int N, S, T;

inline int IN(int n) { return n<<1; }
inline int OUT(int n) { return n<<1|1; }

bool bfs() {
    queue<int> q;
    visited.fill(false);
    visited[IN(S)] = true;
    q.emplace(IN(S));
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int begin = u&1 ? IN(1) : OUT(1);
        int end   = u&1 ? IN(N) : OUT(N);
        for (int v = begin; v <= end; v += 2) {
            if (!visited[v] && cap[u][v] > 0) {
                visited[v] = true;
                pred[v] = u;
                if (v == OUT(T))
                    return true;
                q.emplace(v);
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int M, u, v;
    
    cin >> N >> M >> S >> T;
    for (int n = 1; n <= N; ++n)
        cin >> cap[IN(n)][OUT(n)];
    while (M--) {
        cin >> u >> v;
        cap[OUT(u)][IN(v)] = INF;
        cap[OUT(v)][IN(u)] = INF;
    }

    pred[IN(S)] = 0;
    while (bfs()) {
        int f = INF;
        for (u = OUT(T); u != IN(S); u = pred[u])
            f = min(f, cap[pred[u]][u]);
        for (u = OUT(T); u != IN(S); u = pred[u]) {
            cap[pred[u]][u] -= f;
            cap[u][pred[u]] += f;
        }
    }

    for (int n = 1; n <= N; ++n) {
        if (visited[IN(n)] && !visited[OUT(n)])
            cout << n << ' ';
    }
    cout << '\n';
    return 0;
}
