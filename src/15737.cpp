/*
 * Q15737 - General maximum matching
 * Date: 2023.12.24
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[512];
queue<int> q;
int vis[512], orig[512], par[512], match[512] {}, upd[512] {};
int tag = 0;
int n, m;

int lca(int x, int y) {
    ++tag;
    while (!x || upd[x] != tag) {
        if (x) {
            upd[x] = tag;
            x = orig[par[match[x]]];
        }
        swap(x, y);
    }
    return x;
}

void blossom(int x, int y, int a) {
    while (orig[x] != a) {
        par[x] = y; y = match[x];
        if (vis[y] == 1) { q.emplace(y); vis[y] = 0; }
        orig[x] = orig[y] = a;
        x = par[y];
    }
}

bool bfs(int u) {
    fill(vis+1, vis+n+1, -1);
    iota(orig+1, orig+n+1, 1);
    q = queue<int>(); q.emplace(u); vis[u] = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (vis[y] == -1) {
                par[y] = x; vis[y] = 1;
                if (!match[y]) {
                    while (y) {
                        int py = par[y];
                        int ny = match[py];
                        match[y] = py; match[py] = y;
                        y = ny;
                    }
                    return true;
                }
                q.emplace(match[y]); vis[match[y]] = 0;
            }
            else if (vis[y] == 0 && orig[x] != orig[y]) {
                int a = lca(orig[x], orig[y]);
                blossom(x, y, a); blossom(y, x, a);
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    int ans = 0;
    for (int u = 1; u <= n; ++u) if (!match[u] && bfs(u)) ++ans;
    cout << ans;
    return 0;
}
