/*
 * Q3026 - DP
 * Date: 2022.3.29
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

i64 pw10[16];
vector<int> memo[7];
bitset<10> given(0);
i64 X;

i64 dp(int n, i64 m) {
    if (n < 7) {
        if (m >= (i64)memo[n].size())
            return 0;
        if (memo[n][m] != -1)
            return memo[n][m];
    }
    int k = n/2;
    i64 M = memo[k].size();
    i64 P = 0;
    i64 p = pw10[n - k] % X;
    i64 ret = 0;
    for (i64 m1 = 0; m1 < M; ++m1) {
        i64 tmp = dp(k, m1);
        if (tmp) {
            i64 m2 = (m + X - P) % X;
            tmp *= dp(n - k, m2);
            ret += tmp;
        }
        P = (P + p) % X;
    }
    if (n < 7)
        memo[n][m] = ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string A, B, D;
    cin >> X >> A >> B >> D;

    pw10[0] = 1;
    for (int i = 1; i < 16; ++i)
        pw10[i] = pw10[i-1] * 10;

    memo[0].resize(1, 1);
    memo[1].resize(min(10L, X), 0);
    for (char& d : D) {
        given[d-'0'] = true;
        ++memo[1][(d-'0') % X];
    }
    for (int i = 2; i < 7; ++i)
        memo[i].resize(min(pw10[i], X), -1);

    int a = A.length(), b = B.length();
    i64 cnt = 0, M = 0;
    int i;
    for (i = 0; i < a; ++i) {
        for (char& d : D) if (d > A[i]) {
            i64 m = (M + ((d-'0') * pw10[a-1-i])) % X;
            cnt += dp(a-1-i, m ? X-m : 0);
        }
        if (given[A[i]-'0'])
            M = (M + ((A[i]-'0') * pw10[a-1-i])) % X;
        else break;
    }
    if (i == a && M == 0) ++cnt;

    M = 0;
    for (i = 0; i < b; ++i) {
        for (char& d : D) if (d < B[i]) {
            i64 m = (M + ((d-'0') * pw10[b-1-i])) % X;
            cnt += dp(b-1-i, m ? X-m : 0);
        }
        if (given[B[i]-'0'])
            M = (M + ((B[i]-'0') * pw10[b-1-i])) % X;
        else break;
    }
    if (i == b && M == 0) ++cnt;
    if (given[0]) cnt -= dp(b-1, 0);

    if (a < b) {
        if (given[0])
            cnt += dp(b-1, 0) - dp(a, 0);
        else
            for (i = a+1; i < b; ++i)
                cnt += dp(i, 0);
    }
    else {
        cnt -= dp(a, 0);
        if (given[0])
            cnt += dp(a-1, 0);
    }

    cout << cnt << '\n';
    return 0;
}
