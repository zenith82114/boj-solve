/*
 * Q14853 - Calculus + Bayes' theorem + combinatorics
 * Date: 2023.12.26
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);

    double lgf[2020] { 0. };
    for (int i = 1; i < 2020; ++i) {
        lgf[i] = lgf[i-1] + log(i);
    }

    auto lgc = [lgf] (int n, int m) {
        return lgf[n] - lgf[m] - lgf[n-m];
    };

    int t; cin >> t; while (t--) {
        int n1, m1, n2, m2; cin >> n1 >> m1 >> n2 >> m2;
        double ans = 0.;
        for (int k = m1; k <= m1+m2; ++k) {
            ans += exp(lgc(k, m1) + lgc(n1+n2+1-k, n1-m1) - lgc(n1+n2+2, n1+1));
        }
        cout << ans << '\n';
    }

    return 0;
}
