/*
 * Q1088 - Greedy
 * Date: 2022.6.17
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Rational {
    i64 p, q;
    Rational(): p(0ll), q(1ll) {}
    bool operator<(const Rational& rhs) {
        return p * rhs.q < q * rhs.p;
    }
};
double abs_diff(const Rational& lhs, const Rational& rhs) {
    i64 p = abs(lhs.p * rhs.q - lhs.q * rhs.p);
    i64 q = lhs.q * rhs.q;
    return (double)p / q;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<Rational> v(n);
    for (auto& a : v) cin >> a.p;

    auto a_min = min_element(v.begin(), v.end());
    auto a_max = max_element(v.begin(), v.end());
    double diff_min = abs_diff(*a_min, *a_max);

    int m; cin >> m;
    while (m--) {
        a_max->q++;
        a_min = min_element(v.begin(), v.end());
        a_max = max_element(v.begin(), v.end());
        diff_min = min(diff_min, abs_diff(*a_min, *a_max));
    }

    cout.precision(12);
    cout << diff_min;
    return 0;
}
