/*
 * Q14003 - LIS using binary search
 * Date: 2021.8.25
 */

#include<iostream>
#include<algorithm>
using namespace std;

constexpr int MAX = 1000000;
int A[MAX], least_last[MAX], pos[MAX];

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);

	int N, L, maxL = 0, *p;
	cin >> N;
	fill_n(pos, N, 0);
	for (int n = 0; n < N; ++n) {
		cin >> A[n];
		p = lower_bound(least_last, least_last + maxL, A[n]);
		*p = A[n];
		pos[n] = distance(least_last, p);
		if (p == least_last + maxL) maxL++;
	}
	cout << maxL << endl;
	L = maxL - 1;
	while (L != -1) {
		if (pos[--N] == L)
			least_last[L--] = A[N];
	}
	for (L = 0; L < maxL; cout << least_last[L++] << " ");

	return 0;
}