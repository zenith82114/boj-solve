/*
 * Q1450 - Meet in the middle
 * Date: 2021.7.24
 */

#include<bits/stdc++.h>
using namespace std;

void subset_sums(int l, int r, const vector<int>& A, vector<int64_t>& S)
{
    S[0] = 0;
    int i, j, k = 1;
    for (int n = l; n < r; ++n)
        for (i = 0, j = k; i < j;
            S[k++] = S[i++] + A[n]);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, C; cin >> N >> C;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    // corner case
    if (N == 1) {
        cout << (A[0] > C ? 1 : 2);
        return 0;
    }

    int L1 = 1 << (N/2);
    vector<int64_t> S1(L1);
    subset_sums(0, N/2, A, S1);
    int L2 = 1 << (N - N/2);
    vector<int64_t> S2(L2);
    subset_sums(N/2, N, A, S2);

    int R = 0;
    sort(S1.begin(), S1.end());
    for (const auto& s : S2) {
        auto p = upper_bound(S1.begin(), S1.end(), C - s);
        R += distance(S1.begin(), p);
    }

    cout << R << '\n';
    return 0;
}
