/*
 * Q5977 - DP + subarray minimum w/ monotone deque
 * Date: 2022.1.17
 */

#include<iostream>
#include<deque>
using namespace std;

struct Element {
    int64_t val; int idx;
    Element(int64_t v, int i): val(v), idx(i) {}
};
deque<Element> dq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, K; cin >> N >> K;
    int64_t Sn = 0ll;
    int64_t M = 0ll;
    dq.emplace_back(0, 1);
    for (int n = 0; n < N; ++n) {
        int64_t a; cin >> a;
        // S[n] = sum(A[0]...A[n])
        Sn += a;
        // Q[n] = dp[n-1] - S[n]
        int64_t Qn = M - Sn;
        // dp[n] = max(dp[n-1], S[n] + max(Q[n-K]...Q[n-1]))
        while (!dq.empty() && dq.back().val <= Qn)
            dq.pop_back();
        if (!dq.empty() && dq.front().idx + K < n)
            dq.pop_front();
        M = max(M, Sn + dq.front().val);
        dq.emplace_back(Qn, n);
    }

    cout << M << '\n';
    return 0;
}
