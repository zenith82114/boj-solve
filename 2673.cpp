/*
 * Q2673 - DP
 * Date: 2022.9.16
 */

#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

vector<pii> chords;

int dp[101][101];
int solve(int i, int j) {
    int &ret = dp[i][j];
    if (ret != -1)
        return ret;
    if (i >= j)
        return ret = 0;
    ret = 0;
    bool flag = false;
    for (const pii &c : chords) {
        if (c.first == i && c.second == j)
            flag = true;
        else if (
            i <= c.first && c.first <= j &&
            i <= c.second && c.second <= j
        ) {
            ret = max(ret, solve(i, c.first -1) + solve(c.first, j));
            ret = max(ret, solve(i, c.second) + solve(c.second +1, j));
        }
    }
    return ret += flag;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    chords.resize(N);
    for (pii &c : chords) {
        cin >> c.first >> c.second;
        if (c.first > c.second)
            swap(c.first, c.second);
    }

    memset(dp, -1, sizeof dp);
    cout << solve(1, 100) << '\n';

    return 0;
}
