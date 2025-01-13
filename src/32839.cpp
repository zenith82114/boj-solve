/*
 * Q32839 - DP
 * Date: 2025.1.14
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 26> last;
int dp[3'000'001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    int n = s.size();
    last.fill(n);
    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        int x = s[i] - 'a';
        dp[i] = 1 + *min_element(dp + i + 1, dp + last[x] + 1);
        last[x] = i;
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
}
