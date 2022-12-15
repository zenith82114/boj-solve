/*
 * Q2887 - Minimal spanning tree w/ custom weight function
 * Date: 2021.8.2
 */

#include<bits/stdc++.h>
using namespace std;

struct Point { int id, pos[3]; };

struct Edge {
    int i, j, d;
    Edge(int i, int j, int d)
        :i(i), j(j), d(d) {};
    bool operator<(const Edge& that) const {
        return d > that.d;
    };
};

class union_find {
    vector<int> ar;
public:
    union_find(int sz) : ar(sz, -1) {}
    int find(int x) {
        if (ar[x] < 0) return x;
        return ar[x] = find(ar[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (ar[x] < ar[y]) ar[y] = x;
        else {
            if (ar[x] == ar[y]) --ar[y];
            ar[x] = y;
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        auto& p = points[i];
        p.id = i;
        cin >> p.pos[0] >> p.pos[1] >> p.pos[2];
    }

    priority_queue<Edge> pq;
    for (int d = 0; d < 3; ++d) {
        sort(points.begin(), points.end(), [d](const Point& p, const Point& q) {
            return p.pos[d] < q.pos[d];
        });
        for (int i = 1; i < N; ++i) {
            auto& p1 = points[i], & p2 = points[i - 1];
            pq.emplace(p1.id, p2.id, p1.pos[d] - p2.pos[d]);
        }
    }

    union_find uf(N);
    int cnt = N - 1;
    uint64_t ans = 0ull;
    while (cnt) {
        auto& e = pq.top();
        if (uf.unite(e.i, e.j)) { cnt--; ans += e.d; }
        pq.pop();
    }
    cout << ans << '\n';

    return 0;
}
