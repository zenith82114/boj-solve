/*
 * Q8875 - Binary search + Greedy
 * Date: 2023.3.4
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int A, B, T; cin >> A >> B >> T;

    vector<int> X(A), Y(B);
    for (int& x : X) cin >> x;
    for (int& y : Y) cin >> y;
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end(), greater<int>());

    vector<pair<int, int>> P(T);
    for (auto& [x, y] : P) cin >> x >> y;
    sort(P.begin(), P.end());

    int lo = 1, hi = T+1;
    while (lo < hi) {
        int mid = (lo + hi)>>1;

        priority_queue<int> pq;
        int t = 0;
        for (int& x : X) {
            for (; t < T && P[t].first < x; ++t)
                pq.emplace(P[t].second);
            for (int c = 0; c < mid && !pq.empty(); ++c)
                pq.pop();
        }
        for (; t < T; ++t)
            pq.emplace(P[t].second);

        for (int& y : Y) if (!pq.empty() && pq.top() < y) {
            for (int c = 0; c < mid && !pq.empty(); ++c)
                pq.pop();
        }

        if (pq.empty()) hi = mid;
        else lo = mid + 1;
    }

    cout << (lo > T? -1 : lo);
    return 0;
}
