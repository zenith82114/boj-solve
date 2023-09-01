/*
 * Q13145 - Dijkstra + planar graph dual
 * Date: 2023.9.1
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class DisjSetUnion {
    vector<int> ar;
public:
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
    DisjSetUnion(int sz): ar(sz, -1) {}
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (ar[x] == ar[y]) --ar[x];
        if (ar[x] > ar[y]) swap(x, y);
        ar[y] = x;
    }
};

struct point {
    i64 x, y;
    bool operator<(const point& p) const {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
};

point pt[50'005];
vector<ii> adj[50'005], adj_dual[300'005];
int wei[150'005];
i64 dist[50'005], dist_dualS[300'005], dist_dualT[300'005];

void dijkstra(vector<ii> _adj[], i64 _dist[], int _sz, int _src) {
    fill_n(_dist, _sz, INT64_MAX); _dist[_src] = 0;
    priority_queue<pair<i64, int> > pq; pq.emplace(0, _src);
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop(); du = -du;
        if (_dist[u] < du) continue;
        for (const auto& [m, v] : _adj[u]) {
            if (_dist[v] > _dist[u] + wei[m]) {
                _dist[v] = _dist[u] + wei[m];
                pq.emplace(-_dist[v], v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    for (int u = 1; u <= N; ++u) cin >> pt[u].x >> pt[u].y;

    int M; cin >> M;
    for (int m = 0; m < M; ++m) {
        int u, v; cin >> u >> v >> wei[m];
        adj[u].emplace_back(m, v);
        adj[v].emplace_back(m, u);
    }

    dijkstra(adj, dist, N+1, 1);

    pt[N+1] = { 0, 1'000'000 };
    pt[N+2] = { 1'000'000, 1'000'000 };
    pt[N+3] = { 0, 0 };
    pt[N+4] = { 1'000'000, 0 };

    adj[N+1].emplace_back(M,   N+2); adj[N+2].emplace_back(M,   N+1);
    adj[N+1].emplace_back(M+1, 1  ); adj[1  ].emplace_back(M+1, N+1);
    adj[N+2].emplace_back(M+2, N  ); adj[N  ].emplace_back(M+2, N+2);
    adj[N+3].emplace_back(M+3, 1  ); adj[1  ].emplace_back(M+3, N+3);
    adj[N+4].emplace_back(M+4, N  ); adj[N  ].emplace_back(M+4, N+4);
    adj[N+3].emplace_back(M+5, N+4); adj[N+4].emplace_back(M+5, N+3);

    DisjSetUnion dsu(2*(M+6));

    for (int u = 1; u <= N+4; ++u) {
        const auto& p0 = pt[u];
        auto& au = adj[u];

        sort(au.begin(), au.end(), [&] (const ii& e1, const ii& e2) {
            auto& p1 = pt[e1.second], & p2 = pt[e2.second];
            if ((p0 < p1) != (p0 < p2)) return p2 < p1;
            auto x1 = p1.x - p0.x, y1 = p1.y - p0.y;
            auto x2 = p2.x - p0.x, y2 = p2.y - p0.y;
            return x1*y2 > x2*y1;
        });

        int deg = au.size();
        for (int d = 0; d < deg; ++d) {
            auto [m1, v1] = au[d];
            auto [m2, v2] = au[d+1 == deg? 0 : d+1];
            auto& p1 = pt[v1], & p2 = pt[v2];

            m1 = m1<<1|1; m2 <<= 1;
            if (p1.x > p0.x) m1 ^= 1;
            if (p1.x == p0.x && p1.y < p0.y) m1 ^= 1;
            if (p2.x > p0.x) m2 ^= 1;
            if (p2.x == p0.x && p2.y < p0.y) m2 ^= 1;
            dsu.unite(m1, m2);
        }
    }

    for (int m = 0; m < M; ++m) {
        int u = dsu.find(m<<1), v = dsu.find(m<<1|1);
        adj_dual[u].emplace_back(m, v);
        adj_dual[v].emplace_back(m, u);
    }

    int S = dsu.find(M<<1|1);
    int T = dsu.find((M+5)<<1);
    dijkstra(adj_dual, dist_dualS, 2*(M+6), S);
    dijkstra(adj_dual, dist_dualT, 2*(M+6), T);

    i64 ans = INT64_MAX;
    for (int u = 0; u < 2*(M+6); ++u) {
        for (const auto& [m, v] : adj_dual[u]) {
            ans = min(ans, dist_dualS[u] + dist_dualT[v]);
        }
    }
    ans = -ans;
    for (int m = 0; m < M; ++m) ans += wei[m];

    cout << dist[N] << ' ' << ans;
    return 0;
}
