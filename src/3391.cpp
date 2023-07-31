/*
 * Q3391 - Konig's theorem + Hopcroft-Karp alg.
 * Date: 2023.7.31
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int inf = INT32_MAX;
const int dx[] { -2,-2,-1,-1,1,1,2,2 };
const int dy[] { -1,1,-2,2,-2,2,-1,1 };

int N, nil;
bool flag[200][200];
vector<int> adj[40'000];
vector<int> U;
int level[40'001] {};
int match[40'000] {};

bool bfs() {
    queue<int> q;
    for (int u : U) {
        if (match[u] == nil) {
            level[u] = 0;
            q.emplace(u);
        } else level[u] = inf;
    }
    level[nil] = inf;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == nil) break;
        for (int v : adj[u]) {
            if (level[match[v]] == inf) {
                level[match[v]] = level[u] + 1;
                q.emplace(match[v]);
            }
        }
    }
    return level[nil] != inf;
}

int dfs(int u) {
    if (u == nil) return 1;
    for (int v : adj[u]) if (level[match[v]] == level[u] + 1 && dfs(match[v])) {
        match[v] = u;
        match[u] = v;
        return 1;
    }
    level[u] = inf;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int M; cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        flag[--x][--y] = true;
    }
    nil = N*N;

    for (int x = 0; x < N; ++x)
    for (int y = 0; y < N; ++y) {
        if (flag[x][y]) continue;
        int id = x*N + y;
        match[id] = nil;

        for (int k = 0; k < 8; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (flag[nx][ny]) continue;
            adj[id].emplace_back(nx*N + ny);
        }
        if ((x^y)&1) U.emplace_back(id);
        else adj[id].emplace_back(nil);
    }

    int ans = N*N - M;
    while (bfs()) {
        for (int u : U) if (match[u] == nil) ans -= dfs(u);
    }
    cout << ans;
    return 0;
}
