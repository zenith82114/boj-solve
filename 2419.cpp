/*
 * Q2419 - DP
 * Date: 2022.4.7
 */

#include<bits/stdc++.h>
using namespace std;
const int INF = INT_MAX>>1;

int N, M, res;
vector<int> X;
int memo[301][301][2];

int dp(int l, int r, int t, int n) {
    int ret = INF;
    int dX;
    if (l > r)
        return INF;
    if (!n)
        return 0;
    if (memo[l][r][t] != -1)
        return memo[l][r][t];
    if (l > 0) {
        dX = X[t ? r : l] - X[l-1];
        ret = min(ret, n*dX + dp(l-1, r, 0, n-1));
    }
    if (r < N) {
        dX = X[r+1] - X[t ? r : l];
        ret = min(ret, n*dX + dp(l, r+1, 1, n-1));
    }
    return memo[l][r][t] = ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int s, res;

    cin >> N >> M;
    X.resize(N);
    for (int& x : X) cin >> x;
    X.emplace_back(0);
    sort(X.begin(), X.end());
    s = distance(X.begin(), lower_bound(X.begin(), X.end(), 0));

    res = 0;
    for (int n = 0; n <= N; ++n) {
        memset(memo, -1, sizeof memo);
        res = max(res, n*M - dp(s, s, 0, n));
    }

    cout << res << '\n';
    return 0;
}
