/*
 * Q11378a - bipartite matching
 * Date: 2025.9.12
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> g[1004];
bitset<1004> vis;
int my[1004] {};

int augment(int x) {
    vis.set(x);
    for (int y : g[x]) {
        int z = my[y];
        if (!z || (!vis[z] && augment(z))) {
            my[y] = x;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k >> k;
    for (int x = 1; x <= n; ++x) {
        int d; cin >> d;
        while (d--) {
            int y; cin >> y;
            g[x].emplace_back(y);
        }
    }

    int ans = 0;
    queue<int> q;
    for (int x = 1; x <= n; ++x) {
        vis.reset();
        if (augment(x)) ++ans, q.emplace(x);
    }
    while (k && !q.empty()) {
        int x = q.front(); q.pop();
        vis.reset();
        if (augment(x)) ++ans, q.emplace(x), --k;
    }
    cout << ans;
    return 0;
}
