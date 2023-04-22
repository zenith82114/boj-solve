/*
 * Q2261 - Closest point pair by DnC
 * Date: 2021.7.11
 */

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

struct Point { int x, y; };

uint64_t sqr_dist(Point &p, Point &q) {
    return (uint64_t)(pow(p.x-q.x, 2) + pow(p.y-q.y, 2));
}

uint64_t min_sqr_dist(vector<Point> &V, int l, int r) {
    uint64_t d2 = UINT64_MAX;

    if (r - l < 3) {
        for (int i = l; i < r; ++i)
            for (int j = i+1; j <= r; ++j)
                d2 = min(d2, sqr_dist(V[i], V[j]));
        return d2;
    }

    int m = (l + r) / 2;
    d2 = min(min_sqr_dist(V, l, m), min_sqr_dist(V, m+1, r));
    if (!d2) return 0;

    vector<Point> W;
    int d = (int)ceil(sqrt(d2));
    int t = V[m].x - d;
    for (int i = m; i >= l; --i) {
        if (V[i].x > t)
            W.push_back(V[i]);
        else break;
    }
    t = V[m].x + d;
    for (int i = m+1; i <= r; ++i) {
        if (V[i].x < t)
            W.push_back(V[i]);
        else break;
    }
    sort(W.begin(), W.end(),
    [](const Point& p, const Point& q) { return p.y < q.y; });

    int K = W.size();
    for (int i = 0; i < K; ++i) {
        for (int j = i+1; j < K; ++j) {
            if (W[j].y - W[i].y >= d)
                break;
            d2 = min(d2, sqr_dist(W[i], W[j]));
        }
    }
    return d2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<Point> V(N);
    for (auto& v : V) cin >> v.x >> v.y;
    sort(V.begin(), V.end(),
    [](const Point& p, const Point& q) { return p.x < q.x; });

    cout << min_sqr_dist(V, 0, N-1) << '\n';

    return 0;
}
