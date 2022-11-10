/*
 * Q15718 - Lucas's theorem and Chinese remainder theorem
 * Date: 2022.2.1
 */

#include<bits/stdc++.h>
using namespace std;
constexpr int p1 = 1031, p2 = 97, q1 = 659, q2 = 35, P = 100007;

int powMod(int A, int B, int p)
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

int combModSmall(int n, int k, int p){
    int r = 1;
    if (n < 2*k)
        k = n-k;
    for (int i = n-k+1; i <= n; ++i)
        r = (i*r) % p;
    for (int i = 2; i <= k; ++i)
        r = (powMod(i, p-2, p) * r) % p;
    return r;
}

int combModLarge(int N, int K, int p) {
    int n, k, r = 1;
    while (N && K) {
        n = N%p; N /= p;
        k = K%p; K /= p;
        if (n >= k)
            r = (combModSmall(n, k, p) * r) % p;
        else return 0;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int TC, N, M, r1, r2, r;

    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        if (N > 0 && M > 1 && M <= N+1) {
            r1 = combModLarge(N-1, N-M+1, p1);
            r2 = combModLarge(N-1, N-M+1, p2);
            r = ((p1*q2*r2) + (p2*q1*r1)) % P;
            cout << r << '\n';
        }
        else if (N == 0 && M == 1)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}
