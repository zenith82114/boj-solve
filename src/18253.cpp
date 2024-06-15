/*
 * Q18253 - Dijkstra + DnC
 * Date: 2024.6.15
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
constexpr i64 inf = INT64_MAX;
constexpr int a[] { 0, 1, 0, -1, 0 };

struct query { int r1, c1, r2, c2; };

int n, m;
int v[5][100000];
query que[100000];
i64 ans[100000];

priority_queue<tuple<i64, int, int> > pq;
i64 dist[5][100000];

void dnc(const vector<int>& ids, int lo, int hi) {
    int mid = (lo + hi)>>1;
    for (int s = 0; s < n; ++s) {
        for (int x = 0; x < n; ++x)
        for (int y = lo; y <= hi; ++y) dist[x][y] = inf;
        dist[s][mid] = 0;
        pq.emplace(0, s, mid);

        while (!pq.empty()) {
            auto [d, x, y] = pq.top(); pq.pop();
            d = -d;
            if (dist[x][y] < d) continue;
            for (int k = 0; k < 4; ++k) {
                int nx = x + a[k];
                int ny = y + a[k+1];
                if (nx < 0 || nx == n || ny < lo || ny > hi) continue;
                if (dist[nx][ny] > d + v[nx][ny]) {
                    dist[nx][ny] = d + v[nx][ny];
                    pq.emplace(-dist[nx][ny], nx, ny);
                }
            }
        }

        for (int id : ids) {
            const auto& [r1, c1, r2, c2] = que[id];
            ans[id] = min(ans[id], dist[r1][c1] + dist[r2][c2] + v[s][mid]);
        }
    }

    vector<int> ids_lo, ids_hi;
    for (int id : ids) {
        if (que[id].c2 < mid) ids_lo.emplace_back(id);
        if (que[id].c1 > mid) ids_hi.emplace_back(id);
    }
    if (ids_lo.size()) dnc(ids_lo, lo, mid-1);
    if (ids_hi.size()) dnc(ids_hi, mid+1, hi);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int x = 0; x < n; ++x)
    for (int y = 0; y < m; ++y) cin >> v[x][y];
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        auto& [r1, c1, r2, c2] = que[i];
        cin >> r1 >> c1 >> r2 >> c2;
        --r1; --c1; --r2; --c2;
        if (c1 > c2) { swap(r1, r2); swap(c1, c2); }
        ans[i] = inf;
    }

    vector<int> ids(q); iota(ids.begin(), ids.end(), 0);
    dnc(ids, 0, m-1);
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}
