/*
 * Q1882 - Binary search + DP
 * Date: 2023.11.17
 */

#include<bits/stdc++.h>
using namespace std;

int n, k;
int dp[40001];

int solve(int x) {
    int ans = 0;
    memset(dp+1, 0, n * sizeof(int));
    for (int i = 2; i <= n; ++i) {
        dp[i] += i*x / n;
        ans += dp[i];
        for (int j = 2*i; j <= n; j += i) dp[j] -= dp[i];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> n >> k;
    int l = 1, r = n-1;
    while (l < r) {
        int mid = (l + r)>>1;
        if (solve(mid) < k) l = mid+1;
        else r = mid;
    }

    using ii = pair<int, int>;
    vector<ii> v;
    for (int j = 2; j <= n; ++j) {
        int i = l*j / n;
        if (gcd(i, j) == 1 && i != (l-1)*j / n)
            v.emplace_back(i, j);
    }
    sort(v.begin(), v.end(), [] (const ii& a, const ii& b) {
        return a.first * b.second < b.first * a.second;
    });
    auto [p, q] = v[k - solve(l-1) - 1];
    cout << p << ' ' << q;
    return 0;
}
