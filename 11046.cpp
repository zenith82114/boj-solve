/*
 * Q11046 - Manacher's alg.
 * Date: 2022.2.6
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    N = (N<<1)|1;

    vector<int> value(N);
    for (int i = 1; i < N; i += 2) {
        cin >> value[i];
        value[i+1] = 0;
    }

    vector<int> radius(N);
    int i = 0, r = 0;
    while (i < N) {
        while (i-r-1 >= 0 && i+r+1 < N && value[i-r-1] == value[i+r+1])
            r++;
        radius[i] = r;

        int rj, s;
        for (rj = i+1; rj <= i+r; ++rj) {
            int lj = (i<<1) - rj;
            s = i+r - rj;
            if (radius[lj] != s)
                radius[rj] = min(radius[lj], s);
            else break;
        }
        r = (rj <= i+r) ? s : 0;
        i = rj;
    }

    int M; cin >> M;
    while (M--) {
        int S, E; cin >> S >> E;
        cout << (int)(radius[S+E-1] >= E-S+1) << '\n';
    }

    return 0;
}
