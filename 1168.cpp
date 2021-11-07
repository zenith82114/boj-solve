/*
 * Q1168 - Josephus sequence using segment tree
 * Date: 2021.8.29
 */

#include<iostream>
using namespace std;

// least power of 2 not smaller than n
constexpr int ceil_pow2(int n) {
	// 
	if (n & (n - 1)) {
		for (int i = 1; i < 32; i <<= 1)
			n |= (n >> i);
		return n + 1;
	}
	// n is a power of 2
	return n;
}

// counting segment tree (stores # of elements in interval)
class SegTree {
	int N, * A;
	constexpr int lChild(int n) { return n << 1; }
	constexpr int rChild(int n) { return (n << 1) | 1; }
	void init(int n, int i, int j) {
		if (i == j) A[n] = 1;
		else {
			int m = (i + j) / 2;
			init(lChild(n), i, m);
			init(rChild(n), m + 1, j);
			A[n] = A[lChild(n)] + A[rChild(n)];
		}
	}
	// return and remove the i-th smallest number in {A[l]...A[r]}
	int queryUtil(int n, int l, int r, int i) {
		A[n]--;
		if (l == r) return l;
		int m = (l + r) / 2;
		return i > A[lChild(n)]
			? queryUtil(rChild(n), m + 1, r, i - A[lChild(n)])
			: queryUtil(lChild(n), l, m, i);
	}
public:
	SegTree(int n) {
		N = n;
		A = new int[ceil_pow2(n) << 1]();
		init(1, 1, n);
	}
	int query(int i) {
		return queryUtil(1, 1, N, i);
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, K, i;

	cin >> N >> K;
	SegTree segt(N);

	cout << '<' << segt.query(K);
	for (i = K, --N; N; --N) {
		// calculate the next rank to query
		i += (K - 1);
		i = ((i - 1) % N) + 1;
		cout << ", " << segt.query(i);
	}
	cout << '>';

	return 0;
}