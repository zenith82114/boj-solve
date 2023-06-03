/*
 * Q14878 - Fast Walsh-Hadamard transform
 * Date: 2023.6.3
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void fwht(vector<i64>& A, bool inv) {
    for (int d = 1; d < 1<<16; d *= 2)
    for (int x = 0; x < 1<<16; x += 2*d)
    for (int i = 0; i < d; ++i) {
        i64 a0 = A[x|i], a1 = A[x|d|i];
        A[x|i] = a0 + a1;
        A[x|d|i] = a0 - a1;
        if (inv) A[x|i] /= 2, A[x|d|i] /= 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    vector<i64> A(1<<16); A[0] = 1;
    int s = 0;
    int N; cin >> N;
    for (int i = 0; i < N; ++i) { int x; cin >> x; ++A[s ^= x]; }
    fwht(A, false);
    for (i64& a : A) a *= a;
    fwht(A, true);
    A[0] -= N+1;
    auto mx = max_element(A.begin(), A.end());
    cout << (mx - A.begin()) << ' ' << (*mx)/2;

    return 0;
}
