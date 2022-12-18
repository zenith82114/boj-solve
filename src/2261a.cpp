/*
 * Q2261a - Closest point pair by plane sweep
 * Date: 2022.12.18
 */

#include<bits/stdc++.h>
using namespace std;

using point = pair<int, int>;

int ceil_sqrt(int64_t N) {
    int r = 0;
    for (int k = N>>1; k; k >>= 1)
        while (1ll * (r + k) * (r + k) <= N) r += k;
    return r + (r * r == N? 0 : 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<point> pts(N);
    for (auto& [x, y] : pts) cin >> x >> y;
    sort(pts.begin(), pts.end());

    int ptr = 0;
    int min_sqr_dist = 800'000'000;
    int min_dist = ceil_sqrt(min_sqr_dist);

    struct yx_asc {
        bool operator()(const point& p, const point& q) const {
            return p.second != q.second? p.second < q.second : p.first < q.first;
        };
    };
    set<point, yx_asc> s;

    for (const auto& [xi, yi] : pts) {
        while (ptr < N && pts[ptr].first + min_dist <= xi)
            s.erase(pts[ptr++]);

        auto lb = s.lower_bound({xi, yi - min_dist});
        auto ub = s.upper_bound({xi, yi + min_dist});
        for (auto it = lb; it != ub; ++it) {
            const auto& [xj, yj] = *it;
            int dx = xi - xj;
            int dy = yi - yj;
            int sqr_dist = dx * dx + dy * dy;
            if (min_sqr_dist > sqr_dist) {
                min_sqr_dist = sqr_dist;
                min_dist = ceil_sqrt(min_sqr_dist);
            }
        }

        s.emplace(xi, yi);
    }

    cout << min_sqr_dist << '\n';
    return 0;
}
