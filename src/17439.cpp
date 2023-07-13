/*
 * Q17439 - Aliens trick + Monotone queue opt.
 * Date: 2023.2.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int N, K;
vector<i64> S;

pair<i64, int> solve(i64 lmd, bool final) {
    vector<i64> dp(N+1);
    vector<int> cnt(N+1);
    deque<int> dq { 0 };
    int sz = 1;

    auto cx = [&] (int i, int j) {
        int l = j, r = N+1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (dp[i] + (m - i) * 2*(S[m] - S[i]) >= dp[j] + (m - j) * 2*(S[m] - S[j]))
                r = m;
            else
                l = m+1;
        }
        return l;
    };

    for (int i = 1; i <= N; ++i) {
        while (sz > 1 && cx(dq[0], dq[1]) <= i)
            sz--, dq.pop_front();

        const int& j = dq.front();
        dp[i] = dp[j] + (i - j) * 2*(S[i] - S[j]) - 2*lmd -1;
        if (final) dp[i]++;
        cnt[i] = cnt[j] +1;

        while (sz > 1 && cx(dq[sz-2], dq[sz-1]) >= cx(dq[sz-1], i))
            sz--, dq.pop_back();
        sz++, dq.emplace_back(i);
    }

    return make_pair(dp[N], cnt[N]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> K;
    S.resize(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> S[i];
        S[i] += S[i-1];
    }

    i64 lb = -1e14, ub = 0;
    while (lb < ub) {
        i64 lmd = (lb + ub) >> 1;
        auto [f, k] = solve(lmd, false);
        if (k > K) ub = lmd;
        else lb = lmd+1;
    }

    auto [f, k] = solve(lb, true);
    cout << (f>>1) + lb * K;
    return 0;
}
