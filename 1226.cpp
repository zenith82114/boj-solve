/*
 * Q1226 - Greedy DP
 * Date: 2022.3.20
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int INF = INT_MAX;

struct Item {
    int id, val;
    bool operator<(const Item& rhs) {
        return val > rhs.val;
    }
};
vector<Item> v;
array<int, 100'001> dp;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, K, M;
    vector<int> ans;

    cin >> N;
    v.resize(N);
    K = 0;
    for (int n=0; n<N; ++n) {
        v[n].id = n+1;
        cin >> v[n].val;
        K += v[n].val;
    }
    K >>= 1;

    sort(v.begin(), v.end());
    dp.fill(INF);
    dp[0] = -1;
    M = 0;
    for (int n=0; n<N; ++n) {
        for (int k=0; k<=K; ++k) {
            int kk = k + v[n].val;
            if (dp[k] < n && dp[kk] == INF) {
                dp[kk] = n;
                M = max(M, kk);
            }
        }
    }
    while (M) {
        ans.push_back(v[dp[M]].id);
        M -= v[dp[M]].val;
    }

    cout << ans.size() << '\n';
    for (int& a : ans)
        cout << a << ' ';
    cout << '\n';
    return 0;
}
