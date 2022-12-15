/*
 * Q13261 - Divide-and-Conquer DP
 * Date: 2022.2.17
 */

#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;

vector<u64> S, dp0, dp1;

void dnc(int li, int ri, int lj, int rj) {
    if (li > ri)
        return;
    int i = (li + ri)>>1;
    int J = 0;
    for (int j = min(rj, i); j >= lj; --j) {
        u64 f = dp0[j] + (i - j)*(S[i] - S[j]);
        if (f < dp1[i])
            dp1[i] = f, J = j;
    }
    dnc(li, i-1, lj, J);
    dnc(i+1, ri, J, rj);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    S.resize(N+1, 0ul);
    cin >> S[1];
    for (int n = 2; n <= N; ++n)
        cin >> S[n], S[n] += S[n-1];

    dp0.resize(N+1);
    dp1.resize(N+1);
    for (int n = 0; n <= N; ++n) {
        dp1[n] = n*S[n];
    }
    for (int m = 2; m <= M; ++m) {
        swap(dp0, dp1);
        fill(dp1.begin(), dp1.end(), UINT64_MAX);
        dnc(0, N, 0, N);
    }

    cout << dp1[N] << '\n';
    return 0;
}
