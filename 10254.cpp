/*
 * Q10254 - Farthest point pair on 2D w/ convex hull
 * Date: 2022.1.21
 */

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
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
int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int64_t dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}

// increasing order in angle, then in radius
vec2 orig;
bool polarSort(const vec2& p, const vec2& q) {
    int k = ccw(orig,p,q);
    return k != 0 ? k > 0 : dot(q-p, orig-p) < 0;
}

inline double dist(const vec2& p, const vec2& q) {
    return hypot(p.x - q.x, p.y - q.y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0)->sync_with_stdio(0);
    vector<vec2> points, hull;
    double d, _d;
    int TC, N, M, i, j, j0;
    int P = 0, Q = 0;

    cin >> TC;
    while (TC--) {
        cin >> N;
        points.resize(N);

        // sort points
        M = 0;
        for (int n = 0; n < N; n++) {
            cin >> points[n].x >> points[n].y;
            if (points[n] < points[M])
                M = n;
        }
        swap(points.front(), points[M]);
        orig = points.front();
        sort(++points.begin(), points.end(), polarSort);

        // Graham scan
        M = 0;
        hull.clear();
        for (auto &p : points) {
            while (M > 1 && ccw(hull[M-2], hull[M-1], p) <= 0) {
                hull.pop_back();
                M--;
            }
            hull.push_back(p);
            M++;
        }

        // Rotating calipers
        d = 0.;
        if (M > 3) {
            i = 0, j = 1;
            while (cross(hull[1] - hull[0], hull[(j+1)%M] - hull[j]) > 0)
                j++;
            j0 = j;
            while (i < j0 && j < M) {
                _d = dist(hull[i], hull[j]);
                if (d < _d) {
                    d = _d; P = i; Q = j;
                }
                if (cross(hull[(i+1)%M] - hull[i], hull[(j+1)%M] - hull[j]) < 0)
                    i = (i+1)%M;
                else
                    j = (j+1)%M;
            }
        }
        else {
            for (i = 0; i < M; i++) {
                j = (i+1)%M;
                _d = dist(hull[i], hull[j]);
                if (d < _d) {
                    d = _d; P = i; Q = j;
                }
            }
        }

        cout << hull[P].x << ' ' << hull[P].y << ' '
            << hull[Q].x << ' ' << hull[Q].y << '\n';
    }

    return 0;
}
