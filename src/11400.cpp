/*
 * Q11400 - Bridges
 * Date: 2023.8.22
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> graph[100'001];
int disc[100'001], early[100'001];
vector<pair<int, int> > bridges;
int clk = 0;

void dfs(int pu, int u) {
    disc[u] = early[u] = ++clk;
    for (int& v : graph[u]) {
        if (!disc[v]) {
            dfs(u, v);
            early[u] = min(early[u], early[v]);
            if (disc[u] < early[v])
                bridges.emplace_back(min(u, v), max(u, v));
        }
        else if (v != pu)
            early[u] = min(early[u], disc[v]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int V, E; cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    for (int u = 1; u <= V; ++u) if (!disc[u]) dfs(0, u);

    cout << bridges.size() << '\n';
    sort(bridges.begin(), bridges.end());
    for (const auto& [u, v] : bridges) cout << u << ' ' << v << '\n';
    return 0;
}
