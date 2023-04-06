/*
 * Q2626 - Minimum enclosing circle; gradient descent
 * Date: 2023.4.6
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    struct vec2 {
        double x, y;
        vec2() = default;
        vec2(double x, double y): x(x), y(y) {}

        double norm() const { return hypot(x, y); }
        vec2& operator+=(const vec2& v) {
            x += v.x; y += v.y; return *this;
        }
        vec2 operator-(const vec2& v) const {
            return vec2(x - v.x, y - v.y);
        }
        vec2& operator-=(const vec2& v) {
            x -= v.x; y -= v.y; return *this;
        }
        vec2 operator*(const double c) const {
            return vec2(c * x, c * y);
        }
        vec2& operator/=(const double c) {
            x /= c; y /= c; return *this;
        }
    };

    int N; cin >> N;
    vector<vec2> pts(N);
    vec2 q(0., 0.);
    for (auto& p : pts) {
        cin >> p.x >> p.y;
        q += p;
    }
    q /= N;

    constexpr double eps = 1e-9;
    constexpr double gamma = .99;
    double step = .9;

    int iter = 2048;
    while (iter--) {
        vec2 grad(0., 0.);
        for (const auto& p : pts) {
            vec2 pq = q - p;
            if (grad.norm() < pq.norm()) grad = pq;
        }
        if (grad.norm() < eps) break;
        step *= gamma;
        q -= grad * step;
    }

    cout << fixed << setprecision(3);
    // avoid -0.000
    if (-0.0005 <= q.x && q.x < 0.0005) cout << "0.000 ";
    else cout << q.x << ' ';
    if (-0.0005 <= q.y && q.y < 0.0005) cout << "0.000\n";
    else cout << q.y << '\n';

    double r = 0.;
    for (const auto& p : pts) r = max(r, (q - p).norm());
    cout << r;
    return 0;
}
