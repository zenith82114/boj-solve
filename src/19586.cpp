/*
 * Q19586 - Rotating calipers
 * Date: 2023.6.6
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec2 {
    i64 x, y;
    bool operator<(const vec2& v) const {
        return y != v.y? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
};
inline i64 cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
inline i64 dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
inline i64 ccw(const vec2& o, const vec2& p, const vec2& q) {
    return cross(p - o, q - o);
}

inline double dist(const vec2& p, const vec2& q) {
    return hypot(p.x - q.x, p.y - q.y);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    vector<vec2> points(N);
    for (auto& [x, y] : points) cin >> x >> y;

    swap(points[0], *min_element(points.begin(), points.end()));
    vec2& p0 = points[0];
    sort(++points.begin(), points.end(), [&p0] (const vec2& p1, const vec2& p2) {
        i64 k = ccw(p0, p1, p2);
        return k? k > 0 : dot(p2 - p1, p0 - p1) < 0;
    });

    int M = 0;
    vector<vec2> hull;
    for (const auto &p : points) {
        while (M > 1 && ccw(hull[M-2], hull[M-1], p) <= 0) {
            --M; hull.pop_back();
        }
        ++M; hull.push_back(p);
    }

    auto f = [&hull] (int i, int j, int k) -> i64 {
        return ccw(hull[i], hull[j], hull[k]);
    };
    auto g = [&hull] (int i, int j, int k) -> i64 {
        return dot(hull[j] - hull[i], hull[k] - hull[i]);
    };

    cout << fixed << setprecision(10);
    if (M > 2) {
        int j = 1;
        while (j < M && f(M-1, 0, j) < f(M-1, 0, j+1)) ++j;
        int k = 0;
        while (k < M && g(M-1, 0, k) < g(M-1, 0, k+1)) ++k;
        int l = j;
        while (l < M && g(0, M-1, l) < g(0, M-1, l+1)) ++l;

        auto nxt = [M] (int i) { return i+1 < M? i+1 : 0; };

        double ans = DBL_MAX;
        for (int i = 0; i < M; ++i) {
            int ni = nxt(i);
            while (f(i, ni, j) < f(i, ni, nxt(j))) j = nxt(j);
            while (g(i, ni, k) < g(i, ni, nxt(k))) k = nxt(k);
            while (g(ni, i, l) < g(ni, i, nxt(l))) l = nxt(l);
            double h = f(i, ni, j) / dist(hull[i], hull[ni]);
            double w = dot(hull[ni] - hull[i], hull[k] - hull[l]) / dist(hull[i], hull[ni]);
            ans = min(ans, 2.*(h + w));
        }
        cout << ans;
    }
    else cout << 2.*dist(hull[0], hull[1]);

    return 0;
}
