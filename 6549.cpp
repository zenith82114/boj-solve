/*
 * Q6549 - Largest rectangle in a histogram
 * Date: 2021.7.11
 */

#include<iostream>
#include<algorithm>
using namespace std;

int flrlog2(int n)
{
	int k = 0;
	while (n >>= 1) k++;
	return k;
}
class RMQ {
	int **A;
	int M;
public:
	RMQ(int *H, int N) {
		M = flrlog2(N) + 1;
		A = new int*[M];
		for (int m = 0; m < M; ++m)
			A[m] = new int[N];
		for (int n = 0; n < N; ++n)
			A[0][n] = n;
		for (int m = 1, d = 1; m < M; ++m, d<<=1) {
			for (int n = 0; n + (d<<1) <= N; ++n) {
				A[m][n] = (H[A[m - 1][n]] < H[A[m - 1][n + d]] ?
					A[m - 1][n] : A[m - 1][n + d]);
			}
		}
	}
	int rangeMin(int *H, int l, int r) {
		int m = flrlog2(r - l + 1);
		int d = 1 << m;
		return (H[A[m][l]] < H[A[m][r - d + 1]] ?
			A[m][l] : A[m][r - d + 1]);
	}
	~RMQ() {
		for (int m = 0; m < M; ++m)
			delete[]A[m];
		delete[]A;
	}
};
int64_t maxRectAreaUtil(int *H, RMQ *rmq, int l, int r)
{
	if (l > r) return -1;
	if (l == r) return H[l];
	int m = rmq->rangeMin(H, l, r);
	int64_t M = max(maxRectAreaUtil(H, rmq, l, m - 1),
					maxRectAreaUtil(H, rmq, m + 1, r));
	return max(M, (int64_t)H[m] * (r - l + 1));
}
uint64_t maxRectArea(int *H, int N)
{
	RMQ rmq(H, N);
	return maxRectAreaUtil(H, &rmq, 0, N - 1);
}
int main()
{
	ios::sync_with_stdio(0);
	int N, *H;
	while (cin >> N) {
		if (!N) break;
		H = new int[N];
		for (int n = 0; n < N; ++n)
			cin >> H[n];
		cout << maxRectArea(H, N) << endl;
		delete[]H;
	}
}