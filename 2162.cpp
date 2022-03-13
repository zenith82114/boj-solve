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
}segm[MAX];

int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}
bool intersects(int i, int j)
{
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
    int parent, height, groupSize;
}db[MAX];
int leader(int x)
{
    int& p = db[x].parent;
    if (x == p) return p;
    return p = leader(p);
}
bool sameGroup(int x, int y)
{
    return leader(x) == leader(y);
}
int unite(int x, int y)
{
    int X = leader(x), Y = leader(y);
    Data& dX = db[X], & dY = db[Y];
    if (X == Y) return 0;
    int& hX = dX.height, & hY = dY.height;
    if (hX < hY) {
        dX.parent = Y;
        return dY.groupSize += dX.groupSize;
    } else {
        dY.parent = X;
        if (hX == hY) hX++;
        return dX.groupSize += dY.groupSize;
    }
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, n, m;
    int nG, maxGsize = 1;
    Segment* s;

    cin >> N; nG = N;
    for (n = 0; n < N; ++n) {
        db[n].parent = n;
        db[n].height = 0;
        db[n].groupSize = 1;
        s = &segm[n];
        cin >> s->p1.x >> s->p1.y
            >> s->p2.x >> s->p2.y;
        for (m = 0; m < n; ++m) {
            if (!sameGroup(m, n) && intersects(m, n)) {
                nG--;
                maxGsize = max(maxGsize, unite(m, n));
            }
        }
    }
    cout << nG << '\n' << maxGsize << '\n';

    return 0;
}
