/*
 * Q11111 - min cost flow
 * Date: 2024.8.10
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int MAX = 2502, INF = INT32_MAX;

const int price[6][6] = {
   {10,8,7,5,0,1},
    {8,6,4,3,0,1},
    {7,4,3,2,0,1},
    {5,3,2,2,0,1},
    {0,0,0,0,0,0},
    {1,1,1,1,0,0}
};
int label[50][50];
inline int get_price(int n1, int m1, int n2, int m2) {
    return price[label[n1][m1]][label[n2][m2]];
}

array<array<bool, MAX>, MAX> cap;
array<array<int, MAX>, MAX> cost;
array<vector<int>, MAX> adj;
array<int, MAX> pred, dist;

void add_edge(int u, int v, int w) {
    cap[u][v] = true;
    cost[u][v] = w;
    adj[u].push_back(v);
    cap[v][u] = false;
    cost[v][u] = -w;
    adj[v].push_back(u);
}

bool spfa(int S, int T) {
    queue<int> q;
    bitset<MAX> inq;

    dist.fill(INF);
    dist[S] = 0;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    int S = N*M;
    int T = S+1;
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            char c; cin >> c;
            label[n][m] = c - 'A';
        }
    }

    for (int n = 0, v = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m, ++v) {
            if ((n^m)&1) {
                add_edge(S, v, 0);
                if (n > 0)
                    add_edge(v, v-M, -get_price(n, m, n-1, m));
                if (m > 0)
                    add_edge(v, v-1, -get_price(n, m, n, m-1));
                if (m < M-1)
                    add_edge(v, v+1, -get_price(n, m, n, m+1));
                if (n < N-1)
                    add_edge(v, v+M, -get_price(n, m, n+1, m));
            }
            else add_edge(v, T, 0);
        }
    }

    int ans = 0, cur = 0;
    while (spfa(S, T)) {
        for (int v = T; v != S; v = pred[v]) {
            cap[pred[v]][v] = false;
            cap[v][pred[v]] = true;
            cur += cost[pred[v]][v];
        }
        ans = min(ans, cur);
    }

    cout << -ans << '\n';
    return 0;
}
