/*
 * Q13361 - Ad-hoc; graph theory
 * Date: 2023.5.23
 */

#include<bits/stdc++.h>
using namespace std;

array<vector<int>, 500'000> adj;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int N; cin >> N;
    vector<pair<int, int> > rect(N);
    vector<int> v; v.reserve(2*N);
    i64 ans = 0LL;
    for (auto& [x, y] : rect) {
        cin >> x >> y;
        v.emplace_back(x); v.emplace_back(y);
        ans += x + y;
    }
    sort(v.begin(), v.end());
    auto enc = [&v] (int x) -> int {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    };
    for (auto& [x, y] : rect) {
        x = enc(x), y = enc(y);
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    bitset<500'000> visited;
    queue<int> q;
    for (int i = 0; i < 2*N; i++) if (!adj[i].empty() && !visited[i]) {
        int V = 0, E = 0;
        i64 S = 0LL;
        int M = 0;
        q.emplace(i); visited.set(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            V++; E += adj[x].size();
            S += v[x];
            M = max(M, v[x]);
            for (int y : adj[x]) if (!visited[y]) {
                q.emplace(y); visited.set(y);
            }
        }
        ans -= V == E>>1? S : S - M;
    }
    cout << ans;
    return 0;
}
