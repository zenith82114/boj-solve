/*
 * Q14587 - DP, stack, priority queue
 * Date: 2025.12.22
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using ii = pair<int, int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<u32> x(n), h(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> h[i];

    vector<int> perm(n);
    iota(begin(perm), end(perm), 0);
    sort(begin(perm), end(perm), [&x] (int i, int j) { return x[i] < x[j]; });

    vector<u32> sx(n), sh(n);
    for (int i = 0; i < n; ++i) sx[i] = x[perm[i]], sh[i] = h[perm[i]];
    x.swap(sx), h.swap(sh);

    vector<int> ltop(n), rtop(n);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        ltop[i] = i;
        while (!st.empty() && x[st.top()] + h[i] >= x[i]) {
            ltop[i] = min(ltop[i], ltop[st.top()]);
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i > -1; --i) {
        rtop[i] = i;
        while (!st.empty() && x[st.top()] <= x[i] + h[i]) {
            rtop[i] = max(rtop[i], rtop[st.top()]);
            st.pop();
        }
        st.push(i);
    }

    vector<int> dp(n);
    dp[0] = 1;
    priority_queue<ii, vector<ii>, greater<> > pq;
    pq.emplace(1, 0);
    for (int i = 1; i < n; ++i) {
        dp[i] = 1 + (ltop[i] ? dp[ltop[i] - 1] : 0);
        while (!pq.empty() && rtop[pq.top().second] < i) {
            pq.pop();
        }
        if (!pq.empty()) {
            dp[i] = min(dp[i], pq.top().first);
        }
        pq.emplace(1 + dp[i - 1], i);
    }

    cout << dp[n - 1];
    return 0;
}
