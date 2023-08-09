/*
 * Q7040 - System of difference constraints
 * Date: 2023.1.20
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, ML, MD; cin >> N >> ML >> MD;

    vector<vector<pair<int, int>>> adj(N+1);
    while (ML--) {
        int u, v, d; cin >> u >> v >> d;
        adj[u].emplace_back(v, d);
    }
    while (MD--) {
        int u, v, d; cin >> u >> v >> d;
        adj[v].emplace_back(u, -d);
    }

    constexpr int inf = INT_MAX;
    vector<int> x(N+1, inf); x[1] = 0;
    queue<int> q; q.emplace(1);
    vector<int> inq(N+1, false);
    q.emplace(0);

    int clk = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        if (u == 0) {
            if (++clk == N) break;
            q.emplace(0);
            continue;
        }

        for (const auto& [v, d] : adj[u]) {
            if (x[v] > x[u] + d) {
                x[v] = x[u] + d;
                if (x[v] < 0) {
                    cout << -1;
                    return 0;
                }
                if (!inq[v]) {
                    q.emplace(v);
                    inq[v] = true;
                }
            }
        }
    }

    if (q.empty()) cout << (x[N] == inf? -2 : x[N]);
    else cout << -1;
    return 0;
}
