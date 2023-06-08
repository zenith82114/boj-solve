/*
 * Q20151 - Shamos-Hoey alg.
 * Date: 2023.6.8
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
        return make_pair(x, y) == make_pair(p.x, p.y);
    }
};

struct segment {
    point l, r;
    int id;
    long double eval(i64 x0) const {
        return l.y + (long double)(r.y - l.y) * (x0 - l.x) / (r.x - l.x);
    }
    bool operator<(const segment& seg) const {
        i64 x0 = max(l.x, seg.l.x);
        if (abs(eval(x0) - seg.eval(x0)) > 1e-10L)
            return eval(x0) < seg.eval(x0);
        return id < seg.id;
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

    if (a == c && ccw(a, b, d) != 0) return false;
    if (b == d && ccw(a, b, c) != 0) return false;
    if (a == d || b == c) return false;

    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (!(ab || cd)) return !(b < c || d < a);
    return ab <= 0 && cd <= 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    constexpr i64 K = 2e9 + 1;

    int N; cin >> N;

    vector<segment> segm(N);
    for (int i = 0; i < N; ++i) {
        auto& [l, r, id] = segm[i];
        i64 x, y;
        cin >> x >> y; l.x = K*x - y; l.y = x + K*y;
        cin >> x >> y; r.x = K*x - y; r.y = x + K*y;
        if (r < l) swap(l, r);
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
        const point& p1 = (f1 == 1? segm[i1].l : segm[i1].r);
        const point& p2 = (f2 == 1? segm[i2].l : segm[i2].r);
        return make_tuple(p1.x, f1, p1.y) < make_tuple(p2.x, f2, p2.y);
    });

    multiset<segment> ms;
    vector<multiset<segment>::iterator> ptrs(N);

    for (const auto& [i, f] : evt) {
        if (f == 1) {
            auto it = ms.emplace(segm[i]);
            if (it != ms.begin() && intersect(segm[i], *prev(it))) {
                cout << 1; return 0;
            }
            if (next(it) != ms.end() && intersect(segm[i], *next(it))) {
                cout << 1; return 0;
            }
            ptrs[i] = it;
        }
        else {
            auto it = ptrs[i];
            if (it != ms.begin() && next(it) != ms.end() && intersect(*prev(it), *next(it))) {
                cout << 1; return 0;
            }
            ms.erase(it);
        }
    }
    cout << 0; return 0;
}
