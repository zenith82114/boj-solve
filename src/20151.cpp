/*
 * Q20151 - Shamos-Hoey alg.
 * Date: 2024.11.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;

struct point {
    i64 x, y;
    bool operator<(const point& p) const {
        return make_pair(x, y) < make_pair(p.x, p.y);
    }
    bool operator==(const point& p) const {
        return x == p.x && y == p.y;
    }
};

struct segment {
    point l, r;
    int id;
    long double eval(i64 x) const {
        return l.y + (r.y - l.y) * ((long double)(x - l.x) / (r.x - l.x));
    }
    bool operator<(const segment& seg) const {
        /* assume enough difference on at least one side (left or right) */
        i64 x = max(l.x, seg.l.x);
        if (l == seg.l) x = min(r.x, seg.r.x);
        return 1e-18l < seg.eval(x) - eval(x);
    }
};

int ccw(const point& o, const point& a, const point& b) {
    i128 x1 = a.x - o.x, y1 = a.y - o.y;
    i128 x2 = b.x - o.x, y2 = b.y - o.y;
    i128 k = x1 * y2 - x2 * y1;
    return k? (k > 0? 1 : -1) : 0;
}

bool intersect(const segment& s1, const segment& s2) {
    const auto& [a, b, i1] = s1;
    const auto& [c, d, i2] = s2;

    /* two endpoints touching */
    if (a == c && ccw(a, b, d) != 0) return false;
    if (b == d && ccw(a, b, c) != 0) return false;
    if (a == d || b == c) return false;

    /* general */
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (!(ab || cd)) return !(b < c || d < a);
    return ab <= 0 && cd <= 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    constexpr i64 K = 2'000'000'001;

    int N; cin >> N;

    vector<segment> segm(N);
    for (int i = 0; i < N; ++i) {
        auto& [l, r, id] = segm[i];
        i64 x, y;
        /* remove vertical segments via rotation */
        cin >> x >> y; l.x = K*x - y; l.y = x + K*y;
        cin >> x >> y; r.x = K*x - y; r.y = x + K*y;
        if (r < l) swap(l, r);
        assert(l.x < r.x);
        id = i;
    }

    using ii = pair<int, int>;
    vector<ii> evt;
    for (int i = 0; i < N; ++i) {
        evt.emplace_back(i, 0);
        evt.emplace_back(i, 1);
    }
    sort(evt.begin(), evt.end(), [&] (const ii& e1, const ii& e2) {
        const auto& [i1, f1] = e1;
        const auto& [i2, f2] = e2;
        const point& p1 = (f1 == 0? segm[i1].l : segm[i1].r);
        const point& p2 = (f2 == 0? segm[i2].l : segm[i2].r);
        /* right endpoints (deletions) go first */
        return make_tuple(p1.x, -f1, p1.y) < make_tuple(p2.x, -f2, p2.y);
    });

    set<segment> s;
    vector<set<segment>::iterator> iters(N);

    for (const auto& [i, f] : evt) {
        if (f == 0) {
            auto p = s.lower_bound(segm[i]);
            if (p != s.end() && intersect(*p, segm[i])) {
                cout << 1; return 0;
            }
            if (p != s.begin() && intersect(*prev(p), segm[i])) {
                cout << 1; return 0;
            }
            iters[i] = s.insert(p, segm[i]);
        }
        else {
            auto p = iters[i];
            if (next(p) != s.end() && p != s.begin() && intersect(*next(p), *prev(p))) {
                cout << 1; return 0;
            }
            s.erase(p);
        }
    }
    cout << 0; return 0;
}
