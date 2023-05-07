/*
 * Q1257 - 0-1 BFS
 * Date: 2023.5.7
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    using i64 = int64_t;
    using ii = pair<int, int>;

    i64 M; cin >> M;
    int N; cin >> N;
    vector<int> A(N);
    int P = 0;
    for (int& a : A) cin >> a, P = max(P, a);

    vector<vector<ii> > adj(P);
    for (int x = 0; x < P; ++x) for (int a : A) {
        if (x + a < P) adj[x].emplace_back(x + a, 1);
        else adj[x].emplace_back(x + a - P, 0);
    }
    vector<int> dist(P, P); dist[0] = 0;
    deque<int> dq; dq.emplace_front(0);
    while (!dq.empty()) {
        auto x = dq.front(); dq.pop_front();
        for (auto& [y, w] : adj[x]) if (dist[y] > dist[x] + w) {
            dist[y] = dist[x] + w;
            if (w & 1) dq.emplace_back(y);
            else dq.emplace_front(y);
        }
    }
    cout << dist[M % P] + (M / P);
    return 0;
}
