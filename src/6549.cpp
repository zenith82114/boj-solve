/*
 * Q6549 - Largest rectangle in a histogram w/ sparse table
 * Date: 2021.7.11
 */

#include<iostream>
#include<algorithm>
#include<array>
using namespace std;

array<array<int, 100000>, 17> A;
array<int, 100000> H;

int floor_log2(int n) {
    int k = 0;
    while (n >>= 1) ++k;
    return k;
}

int range_min(int l, int r) {
    int m = floor_log2(r-l+1);
    int d = 1<<m;
    int a1 = A[m][l], a2 = A[m][r-d+1];
    return (H[a1] < H[a2] ? a1 : a2);
}

int64_t max_rect_area(int l, int r) {
    if (l > r)
        return -1;
    if (l == r)
        return (int64_t)H[l];
    int m = range_min(l, r);
    auto a = max(max_rect_area(l, m-1), max_rect_area(m+1, r));
    return max(a, (int64_t)H[m] * (r-l+1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N;
    while (cin >> N) {
        if (!N) break;
        for (int n = 0; n < N; ++n) cin >> H[n];
        int M = 1 + floor_log2(N);
        for (int n = 0; n < N; ++n) A[0][n] = n;
        for (int m = 1, d = 1; m < M; ++m, d <<= 1) {
            for (int n = 0; n + (d<<1) <= N; ++n) {
                int a1 = A[m-1][n], a2 = A[m-1][n+d];
                A[m][n] = (H[a1] < H[a2] ? a1 : a2);
            }
        }
        cout << max_rect_area(0, N-1) << '\n';
    }

    return 0;
}
