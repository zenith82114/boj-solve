/*
 * Q16229 - Z alg.
 * Date: 2022.2.6
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 100'000> Z;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string S;
    int N, K, l, r;

    cin >> N >> K >> S;
    l = r = 0;
    Z[0] = N;
    for (int i = 1; i < N; i++) {
        if (i > r) {
            l = r = i;
            while (r < N && S[r] == S[r-l])
                r++;
            Z[i] = r-l;
            r--;
        }
        else {
            if (Z[i-l] < r-i+1)
                Z[i] = Z[i-l];
            else {
                l = i;
                while (r < N && S[r] == S[r-l])
                    r++;
                Z[i] = r-l;
                r--;
            }
        }
    }
    for (int i = N-1; i > 0; i--) {
        if (i+Z[i] == N && N <= (N+K)/i*i) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << (K < N ? 0 : N) << '\n';
    return 0;
}
