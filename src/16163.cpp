/*
 * Q16163 - Manacher's alg.
 * Date: 2022.2.5
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string S; cin >> S;
    string T(".");
    for (auto& c : S) {
        T.push_back(c);
        T.push_back('.');
    }

    array<int, 4'000'001> radius;
    int N = T.length();
    int i = 0, r = 0;
    ulong cnt = 0ul;
    while (i < N) {
        while (i-r-1 >= 0 && i+r+1 < N && T[i-r-1] == T[i+r+1])
            r++;
        radius[i] = r;
        cnt += (radius[i]+1)>>1;

        int rj, s;
        for (rj = i+1; rj <= i+r; ++rj) {
            int lj = (i<<1) - rj;
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
