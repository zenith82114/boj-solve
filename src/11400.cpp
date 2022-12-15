/*
 * Q11400 - Bridges
 * Date: 2022.8.29
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<int> > graph;
vector<int> disc, early, parent;
vector<pair<int, int> > bridges;
int clk = 0;

void dfs(int u) {
    int child = 0;
    disc[u] = early[u] = clk++;
    for (int& v : graph[u]) {
        if (disc[v] == -1) {
            ++child;
            parent[v] = u;
            dfs(v);
            early[u] = min(early[u], early[v]);
            if (disc[u] < early[v])
                bridges.emplace_back(min(u, v), max(u, v));
        }
        else if (parent[u] != v)
            early[u] = min(early[u], disc[v]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int V, E; cin >> V >> E;
    graph.resize(V+1);
    bridges.reserve(E);
    while (E--) {
        int u, v; cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    disc    .resize(V+1, -1);
    early   .resize(V+1);
    parent  .resize(V+1, 0);
    for (int u = 1; u <= V; ++u)
        if (disc[u] == -1) dfs(u);

    cout << bridges.size() << '\n';
    sort(bridges.begin(), bridges.end());
    for (const auto& e : bridges)
        cout << e.first << ' ' << e.second << '\n';
    return 0;
}
