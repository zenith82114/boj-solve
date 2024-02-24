/*
 * Q14347 - Euler-Lagrange eq. + midpoint method + binary search
 * Date: 2024.2.24
 */

#include<bits/stdc++.h>
using namespace std;

vector<double> C;

double calc_ypp(double x, double y, double yp) {
    double s = 1., t = 1. + yp*yp, sx = 0., sy = 0.;
    for (auto c : C) {
        double isd = 1. / (x*x + (y-c)*(y-c));
        s += isd;
        sx += -2.*(x + (y-c)*yp)*isd*isd;
        sy += 2.*(c-y)*isd*isd;
    }
    return (sy*t - sx*yp)*t/s;
}

pair<double, double> solve(double x, double y, double yp) {
    constexpr int T = 10'000;
    constexpr double h = 20./T;

    double res = 0.;
    for (int t = 0; t <= T; ++t) {
        /* prevent extreme slopes from exploding to +/-nan */
        if (y < -20. || y > +20.) return make_pair(1e9, y);
        double s = 1.;
        for (auto c : C) s +=  1. / (x*x + (y-c)*(y-c));
        res += h * s * sqrt(1. + yp*yp);

        double k1 = h * yp;
        double l1 = h * calc_ypp(x, y, yp);
        double k2 = h * (yp + l1/2.);
        double l2 = h * calc_ypp(x + h/2., y + k1/2., yp + l1/2.);
        x += h;
        y += k2;
        yp += l2;
    }
    return make_pair(res, y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout.precision(8);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; ++tc) {
        int n; double A, B; cin >> n >> A >> B;
        C.resize(n); for (auto& c : C) cin >> c;

        vector<double> v { -2, +2 };
        for (auto c : C) v.emplace_back((c - A)/10.);
        sort(v.begin(), v.end());

        double ans = 1e9;
        for (int i = 0; i <= n; ++i) {
            double ansi = 1e9;
            double lo = v[i], hi = v[i+1];
            while (lo + 1e-5 < hi) {
                double mid = (lo + hi)/2.;
                auto [res, yT] = solve(-10., A, mid);
                ansi = res;
                (yT < B? lo : hi) = mid;
            }
            ans = min(ans, ansi);
        }
        cout << "Case #"<<tc<<": "<<ans<<'\n';
    }

    return 0;
}
