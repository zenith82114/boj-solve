/*
 * Q1319 - Rotational sweeping
 * Date: 2023.12.13
 */

#include<bits/stdc++.h>
using namespace std;

struct vec2 {
    int x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x-v.x, y-v.y };
    }
};
int cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using point = pair<vec2, int>;

    int n; cin >> n;
    vector<point> arr(n);
    for (auto& [v, s] : arr) { cin >> v.x >> v.y >> s; }

    int ans = INT32_MAX;

    for (int i = 0; i < n; ++i) {
        vec2& orig = arr[i].first;
        vector<point> brr;

        int diff = 0;
        for (int j = 0; j < n; ++j) if (i != j) {
            auto [v, s] = arr[j];
            if (v < orig) {
                v.x = 2*orig.x - v.x;
                v.y = 2*orig.y - v.y;
                s = -s;
            }
            brr.emplace_back(v, s);
            diff += s;
        }

        sort(brr.begin(), brr.end(), [&orig] (const point& p1, const point& p2) {
            const vec2& v1 = p1.first;
            const vec2& v2 = p2.first;
            int c = ccw(orig, v1, v2);
            return c? c > 0 : dot(v2 - v1, orig - v1) < 0;
        });

        ans = min(ans, abs(diff + arr[i].second));
        ans = min(ans, abs(diff - arr[i].second));
        for (int l = 0, r = 1; l < n; l = r) {
            while (r < n && ccw(orig, brr[l].first, brr[r].first) == 0) ++r;
            for (int k = l; k < r; ++k) { diff -= 2*brr[k].second; }
            ans = min(ans, abs(diff + arr[i].second));
            ans = min(ans, abs(diff - arr[i].second));
        }
    }

    cout << ans;
    return 0;
}
