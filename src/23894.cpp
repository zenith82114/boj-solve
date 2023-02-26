/*
 * Q23894 - Sparse table
 * Date: 2023.2.26
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    constexpr int INF = INT_MAX;

    int N; cin >> N;

    vector<vector<int>> spt(30, vector<int>(N+1));
    vector<vector<int>> f_rev(N+1);

    int f1; cin >> f1;
    spt[0][1] = 1;
    f_rev[f1].emplace_back(1);
    for (int u = 2; u <= N; ++u) {
        cin >> spt[0][u];
        f_rev[spt[0][u]].emplace_back(u);
    }

    for (int k = 1; k < 30; ++k)
    for (int u = 1; u <= N; ++u)
        spt[k][u] = spt[k-1][spt[k-1][u]];

    vector<int> ord(N+1, INF); ord[1] = 0;
    queue<int> q; q.emplace(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const int& v : f_rev[u]) if (ord[v] == INF) {
            ord[v] = ord[u] +1;
            q.emplace(v);
        }
    }

    int Q; cin >> Q;
    while (Q--) {
        int op; cin >> op;

        if (op & 1) cin >> f1;
        else {
            int m, x; cin >> m >> x;

            if (ord[x] <= m) {
                m -= ord[x];
                x = 1;
                if (ord[f1] != INF) m %= (ord[f1] +1);
                if (m) {
                    m--;
                    x = f1;
                }
            }
            for (int k = 0; m; ++k, m >>= 1)
                if (m & 1) x = spt[k][x];

            cout << x << '\n';
        }
    }

    return 0;
}
