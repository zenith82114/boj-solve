/*
 * Q1077 - Convex polygon intersection
 * Date: 2023.3.3
 */

#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct vec2 {
    T x, y;
    vec2() = default;
    vec2(T x, T y): x(x), y(y) {}
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x - v.x, y - v.y };
    }
};
template<typename T>
T cross(const vec2<T>& v, const vec2<T>& w) {
    return v.x * w.y - v.y * w.x;
}
template<typename T>
int ccw(const vec2<T>& o, const vec2<T>& a, const vec2<T>& b) {
    T c = cross(a - o, b - o);
    return c? c > 0? 1 : -1 : 0;
}
bool intersects(vec2<int> a, vec2<int> b, vec2<int> c, vec2<int> d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (!(ab || cd)) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}
vec2<double> intersect(const vec2<int>& a, const vec2<int>& b,
                       const vec2<int>& c, const vec2<int>& d) {
    int64_t sn = (c.x - a.x) * (c.y - d.y) + (d.x - c.x) * (c.y - a.y);
    int64_t sd = (b.x - a.x) * (c.y - d.y) - (c.x - d.x) * (b.y - a.y);
    int64_t xn = (sd - sn) * a.x + sn * b.x;
    int64_t yn = (sd - sn) * a.y + sn * b.y;
    return { (double)xn / (double)sd, (double)yn / (double)sd };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vec2<int>> A(N), B(M);
    for (auto& [x, y] : A) cin >> x >> y;
    for (auto& [x, y] : B) cin >> x >> y;

    // remove degenerate("flat") vertices
    int sz = 0;
    vector<vec2<int>> C;
    for (const auto& a : A) {
        while (sz > 1 && ccw(C[sz-2], C[sz-1], a) == 0)
            sz--, C.pop_back();
        sz++, C.emplace_back(a);
    }
    A.swap(C);
    N = A.size();

    sz = 0;
    C.clear();
    for (const auto& b : B) {
        while (sz > 1 && ccw(C[sz-2], C[sz-1], b) == 0)
            sz--, C.pop_back();
        sz++, C.emplace_back(b);
    }
    B.swap(C);
    M = B.size();

    vector<vec2<double>> P;

    for (const auto& a : A) {
        bool test = true;
        for (int j = 0; j < M; ++j)
            test = test && (ccw(B[j], B[(j+1)%M], a) == 1);
        if (test)
            P.emplace_back((double)a.x, (double)a.y);
    }
    for (const auto& b : B) {
        bool test = true;
        for (int i = 0; i < N; ++i)
            test = test && (ccw(A[i], A[(i+1)%N], b) == 1);
        if (test)
            P.emplace_back((double)b.x, (double)b.y);
    }
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        const auto& a1 = A[i], & a2 = A[(i+1)%N];
        const auto& b1 = B[j], & b2 = B[(j+1)%M];
        if (intersects(a1, a2, b1, b2))
            P.emplace_back(intersect(a1, a2, b1, b2));
    }

    if (P.size() < 3) {
        cout << 0.0;
        return 0;
    }

    auto f = min_element(P.begin(), P.end());
    swap(*f, P[0]);
    auto p0 = P[0];
    sort(P.begin() +1, P.end(), [&p0] (const vec2<double>& p1, const vec2<double>& p2) {
        return ccw(p0, p1, p2) > 0;
    });

    double ans = 0.0;
    int K = P.size();
    for (int k = 0; k < K; ++k)
        ans += cross(P[k], P[(k+1)%K]);

    cout << fixed << setprecision(16) << 0.5 * ans;
    return 0;
}
