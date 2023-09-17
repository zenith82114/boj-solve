/*
 * Q12876 - Segment tree + Convex hull trick
 * Date: 2023.9.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Line {
    i64 y0, m;
    Line(): y0(INT64_MIN), m(0) {}
    Line(i64 y0, i64 m): y0(y0), m(m) {}
    i64 eval(i64 x) const { return y0 + m*x; }
};

class SegTree {
    vector<vector<Line> > ar;
    int n;
public:
    SegTree(int sz) {
        n = 1; while (n < sz) n *= 2;
        ar.resize(2*n);
    }
    void insert(int i, int j, i64 y0, i64 m) {
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ar[i++].emplace_back(y0, m);
            if (~j&1) ar[j--].emplace_back(y0, m);
        }
    }
    void setup() {
        auto ccw = [] (const Line& a, const Line& b, const Line& c) {
            i64 y1 = a.y0 - b.y0, y2 = b.y0 - c.y0;
            i64 m1 = a.m - b.m, m2 = b.m - c.m;
            return y1*m2 <= y2*m1;
        };
        for (int i = 1; i < 2*n; ++i) {
            vector<Line> nv; int sz = 0;
            auto& v = ar[i];
            sort(v.begin(), v.end(), [] (const Line& a, const Line& b) {
                return a.m != b.m? a.m < b.m : a.y0 < b.y0;
            });
            for (const auto& ln : v) {
                if (sz > 0 && nv[sz-1].m == ln.m)
                    --sz, nv.pop_back();
                while (sz > 1 && ccw(nv[sz-2], nv[sz-1], ln))
                    --sz, nv.pop_back();
                ++sz, nv.emplace_back(ln);
            }
            v.swap(nv);
        }
    }
    i64 query(int i, i64 x) {
        i64 ans = INT64_MIN;
        for (i |= n; i; i >>= 1) if (!ar[i].empty()) {
            const auto& v = ar[i];
            int l = 0, r = v.size() - 1;
            while (l < r) {
                int mid = (l + r)>>1;
                if (v[mid].eval(x) < v[mid+1].eval(x)) l = mid+1;
                else r = mid;
            }
            ans = max(ans, v[l].eval(x));
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    SegTree segt(N+1);
    vector<Line> lines(N+1);
    vector<pair<int, i64> > queries;

    for (int j = 1; j <= N; ++j) {
        int op; cin >> op;
        if (op == 1) {
            cin >> lines[j].m >> lines[j].y0;
        } else if (op == 2) {
            int i; cin >> i;
            segt.insert(i, j, lines[i].y0, lines[i].m);
            lines[i].y0 = INT64_MIN;
        } else {
            i64 x; cin >> x;
            queries.emplace_back(j, x);
        }
    }
    for (int j = 1; j <= N; ++j) if (lines[j].y0 != INT64_MIN) {
        segt.insert(j, N, lines[j].y0, lines[j].m);
    }
    segt.setup();
    for (const auto& [i, x] : queries) {
        i64 ans = segt.query(i, x);
        if (ans == INT64_MIN) cout << "EMPTY\n";
        else cout << ans << '\n';
    }
    return 0;
}
