/*
 * Q28089 - Bitmask + linear algebra
 * Date: 2023.7.25
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int N, M; i64 K; cin >> N >> M >> K;
    vector<bool> s(N, false);
    while (M--) {
        int i; cin >> i; s[i] = true;
    }

    auto t = s;
    for (i64 k = 1; k <= K; k <<= 1) if (k & K) {
        int j1 = k % N;
        int j2 = (-k) % N;
        if (j2 < 0) j2 += N;
        for (int i = 0; i < N; ++i) {
            t[i] = (s[j1] != s[j2]);
            j1 = j1 == N-1? 0 : j1+1;
            j2 = j2 == N-1? 0 : j2+1;
        }
        copy(t.begin(), t.end(), s.begin());
    }

    cout << count(s.begin(), s.end(), true);
    return 0;
}
