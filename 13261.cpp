/*
 * Q13261 - Divide-and-Conquer DP
 * Date: 2022.2.17
 */

#include<bits/stdc++.h>
using namespace std;

vector<ulong> S, dp0, dp1;

void dnc(int li, int ri, int lj, int rj) {
    if (li > ri)
        return;
    int i = (li + ri)>>1;
    ulong f;
    int J;
    for (int j = min(rj, i); j >= lj; j--) {
        f = dp0[j] + (i-j)*(S[i]-S[j]);
        if (f < dp1[i])
            dp1[i] = f, J = j;
    }
    dnc(li, i-1, lj, J);
    dnc(i+1, ri, J, rj);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M;

    cin >> N >> M;
    S.resize(N+1);
    S[0] = 0;
    cin >> S[1];
    for (int n=2; n<=N; n++)
        cin >> S[n], S[n] += S[n-1];
    dp0.resize(N+1), dp1.resize(N+1);
    for (int n=0; n<=N; n++)
        dp1[n] = n*S[n];
    for (int m=2; m<=M; m++) {
        swap(dp0, dp1);
        fill(dp1.begin(), dp1.end(), ULONG_MAX);
        dnc(0, N, 0, N);
    }

    cout << dp1[N] << '\n';
    return 0;
}
