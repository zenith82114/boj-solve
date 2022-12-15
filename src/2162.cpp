/*
 * Q2162 - Line segment intersection and disjoint sets
 * Date: 2021.8.9
 */

#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAX = 3000;

struct vec2 {
    int x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x-v.x, y-v.y };
    }
};
struct Segment {
    vec2 p1, p2;
} segm[MAX];

int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}
bool intersects(int i, int j) {
    vec2 &a = segm[i].p1, &b = segm[i].p2;
    vec2 &c = segm[j].p1, &d = segm[j].p2;
    int ab = ccw(a,b,c) * ccw(a,b,d);
    int cd = ccw(c,d,a) * ccw(c,d,b);
    if (!(ab || cd)) {
        if (b < a) swap(a,b);
        if (d < c) swap(c,d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

struct Data {
    int par, rnk, sz;
} db[MAX];

int find(int x) {
    int& p = db[x].par;
    if (x == p) return p;
    return p = find(p);
}
int unite(int x, int y) {
    int X = find(x), Y = find(y);
    Data& dX = db[X], & dY = db[Y];
    if (X == Y) return 0;
    int& hX = dX.rnk, & hY = dY.rnk;
    if (hX < hY) {
        dX.par = Y;
        return dY.sz += dX.sz;
    } else {
        dY.par = X;
        if (hX == hY) hX++;
        return dX.sz += dY.sz;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    int nG = N;
    int maxG = 1;
    for (int n = 0; n < N; ++n) {
        db[n] = {n, 0, 1};
        auto& s = segm[n];
        cin >> s.p1.x >> s.p1.y >> s.p2.x >> s.p2.y;
        for (int m = 0; m < n; ++m) {
            if (find(m) != find(n) && intersects(m, n)) {
                nG--;
                maxG = max(maxG, unite(m, n));
            }
        }
    }

    cout << nG << '\n' << maxG << '\n';
    return 0;
}
