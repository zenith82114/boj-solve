/*
 * Q1199 - Eulerian circuit; Hierholzer's alg.
 * Date: 2025.10.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<pair<int, int> > g[1000];
vector<pair<int, int> >::iterator iter[1000] {};
bitset<5'000'000> vis;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int id = 0;
    for (int x = 0; x < n; ++x) {
        int degx = 0;
        for (int y = 0; y < n; ++y) {
            int k; cin >> k;
            degx += k;
            if (x < y) while (k--) {
                g[x].emplace_back(y, id);
                g[y].emplace_back(x, id);
                ++id;
            }
        }
        if (degx & 1) { cout << -1; return 0; }
    }
    for (int x = 0; x < n; ++x) iter[x] = g[x].begin();

    stack<int> stk; stk.emplace(0);
    vector<int> path;
    while (!stk.empty()) {
        int x = stk.top();
        while (iter[x] < g[x].end() && vis[iter[x]->second]) ++iter[x];
        if (iter[x] == g[x].end()) {
            stk.pop();
            path.emplace_back(x);
        } else {
            auto [y, i] = *iter[x];
            vis.set(i);
            stk.emplace(y);
        }
    }

    reverse(begin(path), end(path));
    for (int x : path) cout << ++x << ' ';
    return 0;
}
