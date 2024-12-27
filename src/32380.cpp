/*
 * Q32380 - sweeping
 * Date: 2024.12.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

array<int, 300'000> A, B, xlen;
array<i64, 300'000> xsum;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, U, D; cin >> N >> U >> D;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        xlen[i] = 0;
        xsum[i] = 0;
    }
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
        int k = i + (B[i] - A[i]) / (U + D);
        if (A[i] <= B[i] && k < N) {
            xlen[k]++;
            xsum[k] += B[i] - A[i] - 1ll * (k - i) * (U + D);
        }
    }
    i64 ans_delta = 0, ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += min(A[i], B[i]) + ans_delta;
        cout << ans << '\n';
        ans_delta += A[i] <= B[i]? U : -D;
        ans_delta -= xlen[i] * (U + D);
        ans += xsum[i];
    }

    return 0;
}
