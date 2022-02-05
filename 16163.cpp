/*
 * Q16163 - Manacher's alg.
 * Date: 2022.2.5
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 4'000'001> radius;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string S, T;
    int N, i, lj, rj, r, s;
    ulong cnt;

    cin >> S;
    T = ".";
    for (auto& c : S) {
        T.push_back(c);
        T.push_back('.');
    }

    N = T.length();
    i = r = 0;
    cnt = 0;
    while (i < N) {
        while (i-r-1>=0 && i+r+1<N && T[i-r-1]==T[i+r+1])
            r++;
        radius[i] = r;
        cnt += (radius[i]+1)>>1;

        for (rj = i+1; rj <= i+r; rj++) {
            lj = (i<<1) - rj;
            s = i+r - rj;
            if (radius[lj] != s) {
                radius[rj] = min(radius[lj], s);
                cnt += (radius[rj]+1)>>1;
            }
            else break;
        }
        r = (rj <= i+r) ? s : 0;
        i = rj;
    }

    cout << cnt << '\n';
    return 0;
}
