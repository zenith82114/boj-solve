/*
 * Q2081 - System of difference constraints
 * Date: 2024.1.22
 */

#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int> > adj[1024];
int dist[1024] {};
queue<int> q;
bitset<1024> inq;
int cnt[1024];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int x, y, w; char op; cin >> x >> op >> y >> w;
        if (op == '1') { swap(x, y); w = -w; }
        adj[y].emplace_back(x, w);
    }

    for (int x = 1; x <= n; ++x) {
        q.emplace(x); inq.set(x);
        cnt[x] = 1;
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop(); inq.reset(x);
        for (const auto& [y, w] : adj[x]) {
            if (dist[y] > dist[x] + w) {
                dist[y] = dist[x] + w;
                if (!inq[y]) {
                    q.emplace(y); inq.set(y);
                    if (++cnt[y] > n) {
                        cout << -1; return 0;
                    }
                }
            }
        }
    }

    int me = 1 - *min_element(dist + 1, dist + n+1);
    for (int x = 1; x <= n; ++x) {
        dist[x] += me;
        if (dist[x] > 1'000'000) { cout << -1; return 0; }
    }
    for (int x = 1; x <= n; ++x) cout << dist[x] << '\n';
    return 0;
}
