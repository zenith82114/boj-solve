/*
 * Q16003 - Chordal graph
 * Date: 2023.6.24
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    vector<vector<int> > adj(N+1);
    while (M--) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    vector<i64> cnt(N+1);
    vector<int> deg(N+1);
    for (int x = 1; x <= N; ++x) {
        deg[x] = adj[x].size();
        cnt[x] = ((i64)deg[x] * (deg[x] - 1)) >> 1;
    }

    bitset<100'001> nei;
    for (int x = 1; x <= N; ++x) {
        for (int y : adj[x]) nei.set(y);
        for (int y : adj[x]) if (make_pair(deg[y], y) < make_pair(deg[x], x)) {
            for (int z : adj[y]) if (nei[z]) cnt[z]--;
        }
        for (int y : adj[x]) nei.reset(y);
    }

    queue<int> q;
    bitset<100'001> visited;
    for (int x = 1; x <= N; ++x) if (!cnt[x]) {
        q.emplace(x);
        visited.set(x);
    }

    vector<int> ans;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        ans.emplace_back(x);
        for (int y : adj[x]) {
            cnt[y] += deg[x] - deg[y];
            deg[y]--;
            if (!cnt[y] && !visited[y]) {
                q.emplace(y);
                visited.set(y);
            }
        }
    }

    if ((int)ans.size() == N) {
        cout << "1\n";
        for (int x : ans) cout << x << ' ';
    } else cout << 0;
    return 0;
}
