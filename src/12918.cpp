/*
 * Q12918 - Geometry + MCMF
 * Date: 2023.6.6
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[202];
bool cap[202][202];
double cost[202][202];
int pred[202];

bool spfa(int S, int T) {
    queue<int> q; q.emplace(S);
    bitset<202> inq; inq.set(S);
    array<double, 202> dist;
    dist.fill(DBL_MAX); dist[S] = 0.;

    while (!q.empty()) {
        int u = q.front(); q.pop(); inq.reset(u);
        for (int v : adj[u]) if (cap[u][v] && dist[v] > dist[u] + cost[u][v] + 1e-9) {
            dist[v] = dist[u] + cost[u][v];
            pred[v] = u;
            if (!inq[v]) { q.emplace(v); inq.set(v); }
        }
    }
    return dist[T] < DBL_MAX;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    auto add_edge = [] (int u, int v, double w) -> void {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        cap[u][v] = true;
        cap[v][u] = false;
        cost[u][v] = w;
        cost[v][u] = -w;
    };
    auto dist = [] (int x1, int y1, int x2, int y2) -> double {
        return hypot(x2 - x1, y2 - y1);
    };

    int N; cin >> N;
    vector<pair<int, int> > p(N);
    for (auto& [x, y] : p) cin >> x >> y;

    const int S = 2*N, T = 2*N + 1;
    for (int i = 0; i < N; ++i) add_edge(S, i, 0.);
    for (int i = 0; i < N; ++i) add_edge(N+i, T, 0.);
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
        const auto& [xi, yi] = p[i];
        const auto& [xj, yj] = p[j];
        add_edge(i, N+j, 0.5 * dist(xi, yi, -xj, yj));
    }

    double ans = 0.;
    while (spfa(S, T)) {
        for (int u = T; u != S; u = pred[u]) {
            ans += cost[pred[u]][u];
            cap[pred[u]][u] = false;
            cap[u][pred[u]] = true;
        }
    }
    cout << fixed << setprecision(3) << ans;
    return 0;
}
