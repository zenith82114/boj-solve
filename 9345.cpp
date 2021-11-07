/*
 * Q9345 - Swap and min/max queries using segment tree
 * Date: 2021.8.30
 */

#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
constexpr ull MAXMASK = (1LL << 32) - 1, MINMASK = ~MAXMASK;

constexpr int ceil_pow2(int n) {
	if (n & (n - 1)) {
		for (int i = 1; i < 32; i <<= 1)
			n |= (n >> i);
		return n + 1;
	}
	return n;
}
class SegTree {
	int N, * I;
	ull* A;
	constexpr int lChild(int n) { return n << 1; }
	constexpr int rChild(int n) { return n << 1 | 1; }
	constexpr ull join(ull x, ull y) {
		ull z1 = min(x & MINMASK, y & MINMASK),
			z2 = max(x & MAXMASK, y & MAXMASK);
		return z1 | z2;
	}
	void init(int n, int l, int r) {
		A[n] = (ull)l << 32 | r;
		if (l < r) {
			int m = (l + r) / 2;
			init(lChild(n), l, m);
			init(rChild(n), m + 1, r);
			A[n] = join(A[lChild(n)], A[rChild(n)]);
		}
		else I[l] = n;
	}
	void update(int n, ull x) {
		while (n && A[n] != x) {
			A[n] = x;
			int m = n & 1 ? n & -2 : n | 1;
			x = join(x, A[m]);
			n >>= 1;
		}
	}
	ull queryUtil(int n, int l, int r, int i, int j) {
		if (l == i && r == j) return A[n];
		int m = (l + r) / 2;
		if (i > m)
			return queryUtil(rChild(n), m + 1, r, i, j);
		if (j <= m)
			return queryUtil(lChild(n), l, m, i, j);
		return join(queryUtil(rChild(n), m + 1, r, m + 1, j),
					queryUtil(lChild(n), l, m, i, m));
	}
public:
	SegTree(int n) {
		N = n;
		I = new int[n];
		A = new ull[ceil_pow2(n) << 1];
		init(1, 0, n - 1);
	}
	~SegTree() { delete[]I; delete[]A; }
	void swap(int i, int j) {
		ull tmp = A[I[i]];
		update(I[i], A[I[j]]);
		update(I[j], tmp);
	}
	bool query(int i, int j) {
		ull res = queryUtil(1, 0, N - 1, i, j);
		return res == ((ull)i << 32 | j);
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int TC, N, K, q, a, b;

	cin >> TC;
	while (TC--) {
		cin >> N >> K;
		SegTree segt(N);
		while (K--) {
			cin >> q >> a >> b;
			if (q)
				cout << (segt.query(a, b) ? "YES\n" : "NO\n");
			else segt.swap(a, b);
		}
	}

	return 0;
}