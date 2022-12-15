/*
 * Q16229 - Z alg.
 * Date: 2022.2.6
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, K; string S; cin >> N >> K >> S;
    int l = 0, r = 0;

    array<int, 100'000> Z;
    Z[0] = N;
    for (int i = 1; i < N; ++i) {
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
    for (int i = N-1; i > 0; --i) {
        if (i + Z[i] == N && N <= (N + K) / i * i) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << (K < N ? 0 : N) << '\n';
    return 0;
}
