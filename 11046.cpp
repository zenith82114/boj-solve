/*
 * Q11046 - Manacher's alg.
 * Date: 2022.2.6
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 2'000'001> value, radius;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, i, lj, rj, r, s;
    int M, S, E;

    cin >> N;
    N = (N<<1)|1;
    value[0] = 0;
    for (i = 1; i < N; i += 2) {
        cin >> value[i];
        value[i+1] = 0;
    }

    i = r = 0;
    while (i < N) {
        while (i-r-1>=0 && i+r+1<N && value[i-r-1]==value[i+r+1])
            r++;
        radius[i] = r;

        for (rj = i+1; rj <= i+r; rj++) {
            lj = (i<<1) - rj;
            s = i+r - rj;
            if (radius[lj] != s)
                radius[rj] = min(radius[lj], s);
            else break;
        }
        r = (rj <= i+r) ? s : 0;
        i = rj;
    }

    cin >> M;
    while (M--) {
        cin >> S >> E;
        cout << (int)(radius[S+E-1] >= E-S+1) << '\n';
    }

    return 0;
}
