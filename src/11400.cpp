/*
 * Q11400 - Bridges by DFS tree
 * Date: 2024.3.2
 *
 * val[x] := # of back-edges going "over" edge (x, par[x]) in this direction
 */

#include<bits/stdc++.h>
using namespace std;

array<vector<int>, 101010> graph;
array<int, 101010> dep, par, val;

void dfs(int x) {
    val[x] = 0;
    for (int y : graph[x]) {
        if (dep[y] == -1) {
            dep[y] = dep[x] + 1;
            par[y] = x;
            dfs(y);
            val[x] += val[y];
        }
        else if (dep[x] < dep[y]) --val[x];
        else if (dep[x] > dep[y]) ++val[x];
    }
    --val[x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int v, e; cin >> v >> e;
    while (e--) {
        int x, y; cin >> x >> y;
        graph[x].emplace_back(y);
        graph[y].emplace_back(x);
    }

    dep.fill(-1);
    dep[1] = 0;
    par[1] = -1;
    dfs(1);

    vector<pair<int, int> > ans;
    for (int x = 2; x <= v; ++x) if (!val[x]) {
        ans.emplace_back(min(x, par[x]), max(x, par[x]));
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto [x, y] : ans) cout << x<<' '<<y << '\n';

    return 0;
}
