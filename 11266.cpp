/*
 * Q11266 - Articulation points
 * Date: 2022.8.29
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<int> > graph;
vector<int> disc, early, parent, ap;
int clk = 0;

void dfs(int u) {
    int child = 0;
    bool flag = false;
    disc[u] = early[u] = clk++;
    for (int& v : graph[u]) {
        if (disc[v] == -1) {
            ++child;
            parent[v] = u;
            dfs(v);
            early[u] = min(early[u], early[v]);
            flag |= (parent[u] && disc[u] <= early[v]);
        }
        else if (parent[u] != v)
            early[u] = min(early[u], disc[v]);
    }
    flag |= (!parent[u] && child > 1);
    if (flag) ap.emplace_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int V, E; cin >> V >> E;
    graph.resize(V+1);
    while (E--) {
        int u, v; cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    disc    .resize(V+1, -1);
    early   .resize(V+1);
    parent  .resize(V+1, 0);
    ap      .reserve(V);
    for (int u = 1; u <= V; ++u)
        if (disc[u] == -1) dfs(u);

    cout << ap.size() << '\n';
    sort(ap.begin(), ap.end());
    for (int& u : ap) cout << u << ' ';
    return 0;
}
