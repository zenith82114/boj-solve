/*
 * Q1129 - Greedy
 * Date: 2022.11.4
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    sort(A.begin(), A.end());
    int D = max(A[1] - A[0], A[N-1] - A[N-2]);
    for (int i = 0; i+2 < N; ++i)
        D = max(D, A[i+2] - A[i]);

    vector<int> B1, B2;
    int e = A[0];
    for (const int& a : A) {
        if (a - e > D) {
            B2.emplace_back(B1.back());
            B1.pop_back();
            e = B2.back();
        }
        B1.emplace_back(a);
    }
    reverse(B2.begin(), B2.end());

    for (const int& b : B1) cout << b << ' ';
    for (const int& b : B2) cout << b << ' ';

    return 0;
}
