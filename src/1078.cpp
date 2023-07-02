/*
 * Q1078 - Bruteforce
 * Date: 2023.7.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

i64 p10[16];

i64 solve(i64 D, int L) {
    i64 x = 0;
    for (int i = 0; 2*i < L; ++i) {
        i64 d = (D / p10[i]) % 10;
        if (d > 0) {
            x += (10-d) * p10[L-1-i];
            D -= (10-d) * (p10[L-1-i] - p10[i]);
        }
        else if (d < 0) {
            x += (10+d) * p10[i];
            D += (10+d) * (p10[L-1-i] - p10[i]);
        }
        else if (i == 0) {
            x += p10[L-1] + p10[0];
        }
    }
    return D == 0? x : 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    p10[0] = 1;
    for (int i = 1; i < 16; ++i) p10[i] = 10 * p10[i-1];
    i64 D; cin >> D;
    if (D % 9 != 0) { cout << -1; return 0; }
    for (int L = 2; L < 16; ++L) {
        i64 x = solve(D, L);
        if (x != 0) { cout << x; return 0; }
    }
    cout << -1; return 0;
}
