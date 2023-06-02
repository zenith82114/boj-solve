/*
 * Q25563 - Sum over subsets DP
 * Date: 2023.6.2
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    constexpr int M = 1<<20;
    auto neg = [] (int x) -> int { return ~x & (M-1); };

    int N, K; cin >> N >> K;
    vector<int> cnt(M);
    for (int n = 0; n < N; ++n) { int a; cin >> a; ++cnt[a]; }

    int64_t ans3 = K? 0 : -N;
    for (int x = 0; x < M; ++x)
        ans3 += 1LL * cnt[x] * cnt[x ^ K];
    ans3 /= 2;

    auto solve = [&] () -> int64_t {
        vector<int> dp(M);
        for (int x = 0; x < M; ++x)
            dp[x] = (x & K)? 0 : cnt[x | K];

        for (int y = 0; y < 20; ++y)
        for (int x = 0; x < M; ++x)
            if (x & (1<<y)) dp[x] += dp[x ^ (1<<y)];

        int64_t ans = -cnt[K];
        for (int x = 0; x < M; ++x)
            if ((x & K) == K) ans += 1LL * cnt[x] * dp[neg(x)];
        return ans >> 1;
    };

    int64_t ans1 = solve();
    for (int x = 0; x < M/2; ++x) swap(cnt[x], cnt[neg(x)]);
    K = neg(K);
    int64_t ans2 = solve();

    cout << ans1 << ' ' << ans2 << ' ' << ans3;
    return 0;
}
