/*
 * Q6549 - Largest rectangle in a histogram
 * Date: 2021.7.11, 2022.1.29(revised)
 */

#include<iostream>
#include<algorithm>
#include<array>
using namespace std;

array<array<int, 100000>, 17> A;
array<int, 100000> H;

int flrlog2(int n) {
    int k = 0;
    while (n >>= 1)
        k++;
    return k;
}

int rangeMin(int l, int r) {
    int m = flrlog2(r-l+1);
    int d = 1<<m;
    int a1 = A[m][l], a2 = A[m][r-d+1];
    return (H[a1] < H[a2] ? a1 : a2);
}

int64_t maxRectArea(int l, int r) {
    if (l > r)
        return -1;
    if (l == r)
        return (int64_t)H[l];
    int m = rangeMin(l, r);
    auto a = max(maxRectArea(l, m-1), maxRectArea(m+1, r));
    return max(a, (int64_t)H[m] * (r-l+1));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, n, m, d;
    while (cin >> N) {
        if (!N)
            break;
        for (n = 0; n < N; n++)
            cin >> H[n];
        M = flrlog2(N) + 1;
        for (n = 0; n < N; n++)
            A[0][n] = n;
        for (m = 1, d = 1; m < M; m++, d <<= 1) {
            for (n = 0; n + (d<<1) <= N; ++n) {
                int a1 = A[m-1][n], a2 = A[m-1][n+d];
                A[m][n] = (H[a1] < H[a2] ? a1 : a2);
            }
        }
        cout << maxRectArea(0, N-1) << '\n';
    }
}
