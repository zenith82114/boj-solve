/*
 * Q18252 - convex hull, two pointers
 * Date: 2025.1.4
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct vec2 {
    int x, y;
    vec2(int x, int y): x(x), y(y) {}
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
};
inline i64 cross(const vec2& v, const vec2& w) {
    return 1ll*v.x*w.y - 1ll*v.y*w.x;
}
inline i64 ccw(const vec2& o, const vec2& p, const vec2& q) {
    return cross(p - o, q - o);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    int xs, ys, xt, yt; cin >> xt >> yt >> xs >> ys;
    vector<tuple<int, int, int> > v(n);
    for (auto& [y, xl, xr] : v) cin >> y >> xl >> xr;
    v.emplace_back(ys, xs, xs);
    v.emplace_back(yt, xt, xt);
    sort(v.begin(), v.end());

    int m = 0;
    vector<vec2> ch;
    for (const auto& [y, xl, xr] : v) {
        auto p = vec2(xl, y);
        while (m > 1 && ccw(ch[m - 2], ch[m - 1], p) <= 0) {
            --m; ch.pop_back();
        }
        ++m; ch.emplace_back(p);
    }
    --m; ch.pop_back();
    int m2 = 0;
    vector<vec2> ch2;
    reverse(v.begin(), v.end());
    for (const auto& [y, xl, xr] : v) {
        auto p = vec2(xr, y);
        while (m2 > 1 && ccw(ch2[m2 - 2], ch2[m2 - 1], p) <= 0) {
            --m2; ch2.pop_back();
        }
        ++m2; ch2.emplace_back(p);
    }
    --m2; ch2.pop_back();
    m += m2;
    ch.insert(ch.end(), ch2.begin(), ch2.end());

    auto area2 = [&ch] (int i, int j, int k) {
        return abs(ccw(ch[i], ch[j], ch[k]));
    };
    i64 ans = 0;
    for (int i = 0; i + 2 < m; ++i) {
        for (int j = i + 1, k = i + 2; j < m; ++j) {
            while (k + 1 < m && area2(i, j, k) < area2(i, j, k + 1)) ++k;
            ans = max(ans, area2(i, j, k));
        }
    }
    cout << (ans/2) << '.' << ((ans&1)*5);
    return 0;
}
