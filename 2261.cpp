/*
 * Q2261 - Closest point pair on 2D
 * Date: 2021.7.11, 2022.1.29(revised)
 */

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

struct Point { int x, y; };
uint64_t sqrDist(Point &p, Point &q)
{
    return (uint64_t)(pow(p.x-q.x, 2) + pow(p.y-q.y, 2));
}
uint64_t minSqrDist(vector<Point> &V, int l, int r)
{
    vector<Point> W;
    int m, d, t, K;
    uint64_t d2 = UINT64_MAX;

    if (r - l < 3) {
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j <= r; ++j)
                d2 = min(d2, sqrDist(V[i], V[j]));
        return d2;
    }

    m = (l + r) / 2;
    d2 = min(minSqrDist(V, l, m), minSqrDist(V, m+1, r));
    if (!d2)
        return 0;

    d = (int)ceil(sqrt(d2));
    t = V[m].x - d;
    for (int i = m; i >= l; --i) {
        if (V[i].x > t)
            W.push_back(V[i]);
        else break;
    }
    t = V[m].x + d;
    for (int i = m + 1; i <= r; ++i) {
        if (V[i].x < t)
            W.push_back(V[i]);
        else break;
    }
    sort(W.begin(), W.end(),
    [](const Point& p, const Point& q) { return p.y < q.y; });

    K = W.size();
    for (int i = 0; i < K; ++i) {
        for (int j = i + 1; j < K; ++j) {
            if (W[j].y - W[i].y >= d)
                break;
            d2 = min(d2, sqrDist(W[i], W[j]));
        }
    }
    return d2;
}
int main()
{
    ios::sync_with_stdio(0);
    vector<Point> V;
    int N, x, y;
    
    cin >> N;
    for (int n = 0; n < N; ++n) {
        cin >> x >> y;
        V.push_back({x, y});
    }
    sort(V.begin(), V.end(),
    [](const Point& p, const Point& q) { return p.x < q.x; });
    cout << minSqrDist(V, 0, N-1) << '\n';

    return 0;
}
