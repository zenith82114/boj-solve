/*
 * Q1020 - DP
 * Date: 2023.7.13
 */

#include<bits/stdc++.h>
using namespace std;

const int v[10] { 6, 2, 5, 5, 4, 5, 6, 3, 7, 5 };

bool memo[16][128][2] {};

string x, y;
int n;

bool dp(int i, int j, int over) {
    if (i == n) return j == 0 && over == 1;
    if (j < 0) return false;
    if (memo[i][j][over]) return false;

    for (char d = over? '0' : x[i]; d <= '9'; ++d) {
        y.push_back(d);
        if (dp(i + 1, j - v[d-'0'], d > x[i]? 1 : over))
            return true;
        y.pop_back();
    }
    memo[i][j][over] = true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> x;
    n = x.size();
    int m = 0;
    for (char d : x) m += v[d-'0'];
    if (dp(0, m, 0)) {
        cout << stoll(y) - stoll(x);
        return 0;
    }

    int64_t ans = 1;
    for (int i = 0; i < n; ++i) ans *= 10;
    ans -= stoll(x);
    for (char& d : x) d = '0';

    for (int i = 0; i < n; ++i)
    for (int j = 0; j <= 7*n; ++j)
        memo[i][j][0] = memo[i][j][1] = false;
    dp(0, m, 0);
    cout << ans + stoll(y);
    return 0;
}
