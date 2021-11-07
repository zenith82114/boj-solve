/*
 * Q1450 - Knapsack problem (counting version)
 * Date: 2021.7.24
 * 
 * How many subsets of the given numbers sum to <= weight limit?
 */

#include<iostream>
#include<algorithm>
#include<cstdint>
using namespace std;

// enumerate sum of every subset of {A[l] ... A[r]}
void subset_sums(int l, int r, int* A, int64_t* S)
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

	int A[30];
	int N, C, N_;
	int L1, L2, R;
	int64_t *S1, *S2, *p;

	cin >> N >> C;
	for (int i = 0; i < N; cin >> A[i++]);

	// corner case
	if (N == 1) {
		cout << (A[0] > C ? 1 : 2);
		return 0;
	}

	N_ = N >> 1;
	L1 = 1 << N_; L2 = 1 << (N - N_);
	S1 = new int64_t[L1]; subset_sums(0, N_, A, S1);
	S2 = new int64_t[L2]; subset_sums(N_, N, A, S2);
	sort(S1, S1 + L1);
	R = 0;
	for (int i = 0; i < L2; ++i) {
		p = upper_bound(S1, S1 + L1, C - S2[i]);
		R += distance(S1, p);
	}
	delete[]S1; delete[]S2;

	cout << R;
	return 0;
}