/*
 * Q1591 - Eulerian path
 * Date: 2023.8.4
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[1000] {};
int ideg[1000] {}, odeg[1000] {};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    vector<vector<int> > vv, ve;
    vector<int> e(M);
    for (int i = M; i <= N; ++i) {
        for (int& a : e) cin >> a;
        ve.emplace_back(e);
        vv.emplace_back(e.begin(), e.end() - 1);
        vv.emplace_back(e.begin() + 1, e.end());
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());

    for (const auto& e : ve) {
        int x = lower_bound(vv.begin(), vv.end(),
            vector<int>(e.begin(), e.end() - 1)) - vv.begin();
        int y = lower_bound(vv.begin(), vv.end(),
            vector<int>(e.begin() + 1, e.end())) - vv.begin();
        adj[x].emplace_back(y);
        odeg[x]++;
        ideg[y]++;
    }

    int src = 0;
    for (size_t x = 0; x < vv.size(); ++x) {
        if (odeg[x] == ideg[x] + 1) { src = x; break; }
    }

    stack<int> stk; stk.emplace(src);
    vector<int> path;
    while (!stk.empty()) {
        int x = stk.top();
        if (!adj[x].empty()) {
            int y = adj[x].back(); adj[x].pop_back();
            stk.emplace(y);
        } else {
            path.emplace_back(x);
            stk.pop();
        }
    }

    for (int a : vv[path.back()]) cout << a << ' ';
    path.pop_back();
    reverse(path.begin(), path.end());
    for (int x : path) cout << vv[x].back() << ' ';

    return 0;
}
