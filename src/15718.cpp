/*
 * Q15718 - Lucas's theorem and Chinese remainder theorem
 * Date: 2022.2.1
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int p1 = 1031, p2 = 97, q1 = 659, q2 = 35, P = 100007;

int pow_mod(int A, int B, int p)
{
    int a = A%p;
    int b = B;
    int r = b&1 ? a : 1;
    while (b >>= 1) {
        a = (a*a) % p;
        if (b&1)
            r = (a*r) % p;
    }
    return r;
}

int comb_mod_small(int n, int k, int p){
    int r = 1;
    if (n < 2*k)
        k = n-k;
    for (int i = n-k+1; i <= n; ++i)
        r = (i*r) % p;
    for (int i = 2; i <= k; ++i)
        r = (pow_mod(i, p-2, p) * r) % p;
    return r;
}

int comb_mod_large(int N, int K, int p) {
    int n, k, r = 1;
    while (N && K) {
        n = N%p; N /= p;
        k = K%p; K /= p;
        if (n >= k)
            r = (comb_mod_small(n, k, p) * r) % p;
        else return 0;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int N, M; cin >> N >> M;
        if (N > 0 && M > 1 && M <= N+1) {
            int r1 = comb_mod_large(N-1, M-2, p1);
            int r2 = comb_mod_large(N-1, M-2, p2);
            int r = ((p1*q2*r2) + (p2*q1*r1)) % P;
            cout << r << '\n';
        }
        else if (N == 0 && M == 1)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}
