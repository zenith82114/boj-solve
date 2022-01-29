/*
 * Q1450 - Knapsack problem (counting version)
 * Date: 2021.7.24
 * 
 * How many subsets of the given numbers sum to <= weight limit?
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> A;
vector<int64_t> S1, S2;

// enumerate sum of every subset of {A[l] ... A[r]}
void subset_sums(int l, int r, vector<int>& A, vector<int64_t>& S)
{
    S[0] = 0;
    int i, j, k = 1;
    for (int n = l; n < r; ++n)
        for (i = 0, j = k; i < j;
            S[k++] = S[i++] + A[n]);
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int N, C, N_, L1, L2, R;

    cin >> N >> C;
    A.resize(N);
    for (int i = 0; i < N; cin >> A[i++]);

    // corner case
    if (N == 1) {
        cout << (A[0] > C ? 1 : 2);
        return 0;
    }

    N_ = N >> 1;
    L1 = 1 << N_; L2 = 1 << (N - N_);
    S1.resize(L1);
    subset_sums(0, N_, A, S1);
    S2.resize(L2);
    subset_sums(N_, N, A, S2);
    sort(S1.begin(), S1.end());

    R = 0;
    for (auto& s : S2) {
        auto p = upper_bound(S1.begin(), S1.end(), C - s);
        R += distance(S1.begin(), p);
    }

    cout << R << '\n';
    return 0;
}
