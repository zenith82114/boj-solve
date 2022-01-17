/*
 * Q5977 - DP + subarray minimum w/ deque
 * Date: 2022.1.17
 */

#include<iostream>
#include<deque>
using namespace std;

struct Element { int64_t val; int idx; };
deque<Element> dq;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    int64_t a, Qn, Sn, M;

    cin >> N >> K;
    Sn = 0;
    M = 0;
    dq.push_back({0, -1});
    for (int n = 0; n < N; n++) {
        cin >> a;
        // S[n] = sum(A[0]...A[n])
        Sn += a;
        // Q[n] = dp[n-1] - S[n]
        Qn = M - Sn;
        // dp[n] = max(dp[n-1], S[n] + max(Q[n-K]...Q[n-1]))
        while (!dq.empty() && dq.back().val <= Qn)
            dq.pop_back();
        if (!dq.empty() && dq.front().idx + K < n)
            dq.pop_front();
        M = max(M, Sn + dq.front().val);
        dq.push_back({Qn, n});
    }

    cout << M << '\n';
    return 0;
}
