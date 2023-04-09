/*
 * Q15308 - Planar graph dual
 * Date: 2023.4.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

class UnionFind {
    vector<int> ar;
public:
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
    UnionFind(int sz): ar(sz, -1) {}
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (ar[x] == ar[y]) ar[x]--;
        if (ar[x] > ar[y]) swap(x, y);
        ar[y] = x;
    }
};

struct point {
    i64 x, y;
    point() = default;
    point(i64 x, i64 y): x(x), y(y) {}
    bool operator<(const point& p) const {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
};

struct line {
    static double t;
    double y0, m;
    int id;
    line(point p1, point p2, int id): id(id) {
        if (p2 < p1) swap(p1, p2);
        m = (double)(p2.y - p1.y) / (p2.x - p1.x);
        y0 = p1.y - m * p1.x;
    }
    bool operator<(const line& l) const {
        return y0 + m * t < l.y0 + l.m * t;
    }
};
double line::t = 0.;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<point> pt(N+1);
    for (int n = 1; n <= N; ++n) {
        auto& [x, y] = pt[n]; cin >> x >> y;
    }

    vector<vector<ii> > adj(N+1);
    vector<int> wei(M);
    for (int m = 0; m < M; ++m) {
        int u, v; cin >> u >> v >> wei[m];
        adj[u].emplace_back(m, v);
        adj[v].emplace_back(m, u);
    }

    /* aggregate auxiliary vertices [0, 2M) into dual vertices */

    UnionFind uf(2*M);

    for (int n = 1; n <= N; ++n) {
        const auto& o = pt[n];
        auto& adjn = adj[n];

        sort(adjn.begin(), adjn.end(), [&] (const ii& a, const ii& b) {
            auto& pa = pt[a.second], & pb = pt[b.second];
            if ((o < pa) != (o < pb)) return pb < pa;
            auto x1 = pa.x - o.x, y1 = pa.y - o.y;
            auto x2 = pb.x - o.x, y2 = pb.y - o.y;
            return x1 * y2 > x2 * y1;
        });

        int deg = adjn.size();
        for (int d = 0; d < deg; ++d) {
            auto [m1, v1] = adjn[d];
            auto [m2, v2] = adjn[(d+1)%deg];
            auto& p1 = pt[v1], & p2 = pt[v2];
            m1 = m1<<1|1; m2 <<= 1;

            if (p1.x > o.x) m1 ^= 1;
            if (p1.x == o.x && p1.y < o.y) m1 ^= 1;
            if (p2.x > o.x) m2 ^= 1;
            if (p2.x == o.x && p2.y < o.y) m2 ^= 1;
            uf.unite(m1, m2);
        }
    }

    /* sorted roots */
    vector<int> sr;
    for (int m = 0; m < 2*M; ++m)
        if (m == uf.find(m)) sr.emplace_back(m);

    /* map auxiliary vertex to dual vertex */

    const auto get_dv = [&sr, &uf] (int u) {
        return lower_bound(sr.begin(), sr.end(), uf.find(u)) - sr.begin();
    };

    /* Floyd-Warshall */

    int F = sr.size();
    assert(N - M + F == 2);

    vector<vector<i64> > dist(F, vector<i64>(F, INT64_MAX>>1));
    for (int i = 0; i < F; ++i) dist[i][i] = 0L;
    for (int m = 0; m < M; ++m) {
        int i = get_dv(m<<1);
        int j = get_dv(m<<1|1);
        dist[i][j] = min(dist[i][j], (i64)wei[m]);
        dist[j][i] = min(dist[j][i], (i64)wei[m]);
    }
    for (int k = 0; k < F; ++k)
    for (int i = 0; i < F; ++i)
    for (int j = 0; j < F; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    /* map query points to dual vertices */

    /* events to sweep in x-axis */
    vector<pair<point, i64> > evt;
    for (int n = 1; n <= N; ++n) evt.emplace_back(pt[n], n);

    int Q; cin >> Q;
    for (int q = 1; q <= Q; ++q) {
        i64 x, y; cin >> x >> y;
        evt.emplace_back(point(x, y), -q);
    }
    sort(evt.begin(), evt.end());

    /* query id -> dual vertex */
    vector<int> dv(Q+1);
    set<line> sl;
    vector<bool> chk(M);

    /* dual vertex corresponding to the outer face of primal graph */
    int f = min_element(pt.begin()+1, pt.end()) - pt.begin();
    dv[0] = get_dv(adj[f][0].first<<1|1);

    for (const auto& [p, i] : evt) {
        if (i > 0) { /* primal vertex */
            line::t = p.x - 0.5;
            for (const auto& [m, v] : adj[i]) {
                if (!chk[m]) continue;
                if (pt[i].x == pt[v].x) continue;
                sl.erase(sl.lower_bound(line(pt[i], pt[v], m)));
            }
            line::t = p.x + 0.5;
            for (const auto& [m, v] : adj[i]) {
                if (chk[m]) continue;
                if (pt[i].x == pt[v].x) continue;
                chk[m] = true;
                sl.emplace(pt[i], pt[v], m);
            }
        } else { /* query point */
            line::t = p.x;
            int q = -i;
            auto lb = sl.lower_bound(line(p, point(p.x+1, p.y), 0));
            dv[q] = lb != sl.end()? get_dv((lb->id)<<1|1) : dv[0];
        }
    }

    for (int q = 1; q <= Q; ++q)
        cout << dist[dv[q-1]][dv[q]] << '\n';

    return 0;
}
