/*
 * Q5419 - Sweep + segment tree
 * Date: 2021.12.23
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class SegTree {
	int N;
	vector<int> A;
	constexpr int ceil_pow2(int n) {
		if (n & (n - 1)) {
			for (int i = 1; i < 32; i <<= 1)
				n |= (n >> i);
			return n + 1;
		}
		return n;
	}
	constexpr int lChild(int n) { return n << 1; }
	constexpr int rChild(int n) { return n << 1 | 1; }
	int removeUtil(int k, int n, int l, int r) {
		int m;
		A[n]--;
		if (l != r) {
			m = (l + r) / 2;
			return k > m
				? removeUtil(k, rChild(n), m + 1, r)
				: removeUtil(k, lChild(n), l, m) + A[rChild(n)];
		}
		else return A[n];
	}
public:
	SegTree(int _N) {
		N = _N;
		A.resize(2 * ceil_pow2(N), 0);
	}
	void insert(int k) {
		int n = 1, l = 0, r = N - 1;
		int m;
		A[1]++;
		while (l < r) {
			m = (l + r) / 2;
			if (k > m) {
				l = m + 1;
				n = rChild(n);
			}
			else {
				r = m;
				n = lChild(n);
			}
			A[n]++;
		}
	}
	// remove k and count (remaining) elements >= k
	int remove(int k) {
		return removeUtil(k, 1, 0, N - 1);
	}
};

struct Point { int x, y; };
vector<Point> points;

// coordinate compression
vector<int> y_idx;
int yToIdx(int y) {
	auto p = lower_bound(y_idx.begin(), y_idx.end(), y);
	return distance(y_idx.begin(), p);
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int TC, N;
	int64_t cnt;
	int x, y;

	cin >> TC;
	for (int tc = 0; tc < TC; tc++) {
		cnt = 0;
		cin >> N;
		points.resize(N);
		y_idx.resize(N);
		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			points[i] = {x, y};
			y_idx[i] = y;
		}

		sort(points.begin(), points.end(),
			[](const Point& p1, const Point& p2){
				return p1.x != p2.x ? p1.x > p2.x : p1.y < p2.y;
			}
		);
		sort(y_idx.begin(), y_idx.end());

		SegTree segt(N);
		for (auto p : points)
			segt.insert(yToIdx(p.y));
		for (auto p : points)
			cnt += segt.remove(yToIdx(p.y));

		cout << cnt << '\n';
	}

	return 0;
}
