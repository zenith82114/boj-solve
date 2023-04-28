/*
 * Q1557 - Inclusion/Exclusion w/ Mobius function
 * Date: 2023.4.28
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    using i64 = int64_t;
    constexpr int LIM = 45000;

    vector<int> mu(LIM); mu[1] = 1;
    for (int i = 1; i < LIM; ++i)
    for (int j = 2 * i; j < LIM; j += i)
        mu[j] -= mu[i];

    int K; cin >> K;
    i64 l = 1, r = 2e9;
    while (l < r) {
        i64 m = (l + r) >> 1;
        i64 k = 0;
        for (int i = 1; i * i <= m; ++i)
            k += mu[i] * (m / (i * i));
        if (k < K) l = m+1; else r = m;
    }
    cout << l;
    return 0;
}
