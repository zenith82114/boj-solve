/*
 * Q2162 - Line segment intersection and disjoint sets
 * Date: 2021.8.9
 */

#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 3000;

struct vec2 {
    int x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x-v.x, y-v.y };
    }
};

pair<vec2, vec2> segm[MAXN];

int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}
bool intersects(int i, int j) {
    auto& [a, b] = segm[i];
    auto& [c, d] = segm[j];
    int ab = ccw(a,b,c) * ccw(a,b,d);
    int cd = ccw(c,d,a) * ccw(c,d,b);
    if (!(ab || cd)) {
        if (b < a) swap(a,b);
        if (d < c) swap(c,d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

int ar[MAXN];

int find(int x) {
    if (ar[x] < 0) return x;
    return ar[x] = find(ar[x]);
}
int unite(int x, int y) {
    x = find(x), y = find(y);
    if (ar[x] > ar[y]) swap(x, y);
    ar[x] += ar[y];
    ar[y] = x;
    return -ar[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    int nG = N;
    int maxG = 1;
    for (int n = 0; n < N; ++n) {
        ar[n] = -1;
        auto& [a, b] = segm[n];
        cin >> a.x >> a.y >> b.x >> b.y;
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
