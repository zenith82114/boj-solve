/*
 * Q1093 - 0-1 Knapsack + meet in the middle
 * Date: 2023.7.1
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int N; cin >> N;
    vector<int> pri(N); for (int& p : pri) cin >> p;
    vector<int> val(N); for (int& v : val) cin >> v;
    int K; cin >> K;

    const int M = N>>1;
    vector<pair<int, int> > ar;
    for (i64 msk = 0; msk < (i64)1<<N; msk += (1<<M)) {
        int v = 0, p = 0;
        for (int i = M; i < N; ++i) if (msk & (1<<i))
            v += val[i], p += pri[i];
        ar.emplace_back(v, p);
    }
    sort(ar.begin(), ar.end());
    for (int i = (int)ar.size() - 1; i > 0; --i)
        ar[i-1].second = min(ar[i-1].second, ar[i].second);

    int cost = INT32_MAX;
    for (i64 msk = 0; msk < 1<<M; ++msk) {
        int v = 0, p = 0;
        for (int i = 0; i < M; ++i) if (msk & (1<<i))
            v += val[i], p += pri[i];
        auto lb = lower_bound(ar.begin(), ar.end(), make_pair(K - v, 0));
        if (lb != ar.end()) cost = min(cost, p + lb->second);
    }

    int T; cin >> T;
    int L = 0;
    while (T--) { int i; cin >> i; L += pri[i]; }
    if (cost == INT32_MAX) cout << -1;
    else cout << max(0, cost - L);
    return 0;
}
