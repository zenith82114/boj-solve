/*
 * Q22975 - DP
 * Date: 2024.10.30
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int64_t> H(n); for (auto& h : H) cin >> h;
    vector<ii> v;
    for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
        v.emplace_back(i, j);
    }
    stable_sort(v.begin(), v.end(), [&H] (const ii& a, const ii& b) {
        auto [ai, aj] (a);
        auto [bi, bj] (b);
        int ax = aj - ai;
        auto ay = H[aj] - H[ai];
        int bx = bj - bi;
        auto by = H[bj] - H[bi];
        return ay * bx < by * ax;
    });
    vector<int> dp(n, 1);
    for (const auto& [i, j] : v) {
        dp[j] = max(dp[j], dp[i] + 1);
    }
    cout << (n - *max_element(dp.begin(), dp.end()));

    return 0;
}
