/*
 * Q11377 - Advanced bipartite matching as maximum flow
 * Date: 2022.9.27
 */

#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

vector<vector<pii>> adj;    // <vertex_id, edge_id>
vector<int> cap;            // [edge_id] -> cap
vector<bool> visited;

void add_edge(int u, int v, int c) {
    adj[u].emplace_back(v, cap.size());
    cap.emplace_back(c);
    adj[v].emplace_back(u, cap.size());
    cap.emplace_back(0);
}

bool bfs(int s, int t, vector<pii> &pred) {
    queue<int> q; q.push(s);
    fill(visited.begin(), visited.end(), false);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto &e : adj[u]) {
            const int &v = e.first;
            const int &z = e.second;
            if (!visited[v] && cap[z] > 0) {
                pred[v] = make_pair(u, z);
                if (v == t)
                    return true;
                visited[v] = true;
                q.emplace(v);
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;
    const int S = 0;
    const int U = N+M+1;
    const int T = U+1;
    adj.resize(T+1);

    add_edge(S, U, K);
    for (int i = 1; i <= N; ++i) {
        add_edge(S, i, 1);
        add_edge(U, i, 1);
        int D; cin >> D;
        while (D--) {
            int j; cin >> j;
            add_edge(i, N+j, 1);
        }
    }
    for (int j = 1; j <= M; ++j)
        add_edge(N+j, T, 1);

    vector<pii> pred(T+1);
    visited.resize(T+1);
    int ans = 0;

    while (bfs(S, T, pred)) {
        ++ans;
        for (int v = T; v != S; v = pred[v].first) {
            int &z = pred[v].second;
            --cap[z];
            ++cap[z^1];
        }
    }

    cout << ans << '\n';
    return 0;
}
