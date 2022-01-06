/*
 * Q7626 - Union area of rectangles using sweep line + segment tree
 * Date: 2022.1.6
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct Edge {
	bool isLeftEdge;
	int x;
	int y1, y2;
	bool operator<(const Edge &e) {
		return x < e.x;
	}
};
vector<Edge> edges;

// coordinate compression
vector<int> Ys;
int yCoordToIndex(int y) {
	return distance(Ys.begin(), lower_bound(Ys.begin(), Ys.end(), y));
}
int yIndexToCoord(int i) {
	return Ys[i];
}

class SegTree {
	int N;
	vector<int> cnt, len;
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
	void addRangeUtil(int n, int l, int r, int i, int j, int k) {
		int m;
		if (i == l && j == r)
			cnt[n] += k;
		else {
			m = (l + r) / 2;
			if (m >= j)
				addRangeUtil(lChild(n), l, m, i, j, k);
			else if (m <= i)
				addRangeUtil(rChild(n), m, r, i, j, k);
			else {
				addRangeUtil(lChild(n), l, m, i, m, k);
				addRangeUtil(rChild(n), m, r, m, j, k);
			}
		}
		if (cnt[n] > 0)
			len[n] = yIndexToCoord(r) - yIndexToCoord(l);
		else if (l + 1 == r)
			len[n] = 0;
		else
			len[n] = len[lChild(n)] + len[rChild(n)];
	}
public:
	SegTree(int _N) {
		int size = 2 * ceil_pow2(_N);
		N = _N;
		cnt.assign(size, 0);
		len.assign(size, 0);
	}
	void addRange(int i, int j, int k) {
		addRangeUtil(1, 0, N-1, i, j, k);
	}
	int query() {
		return len[1];
	}
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, x1, x2, y1, y2;
	int x_prev;
	uint64_t L, S;

	cin >> N;
	edges.resize(2*N);
	Ys.resize(2*N);
	for (int i = 0; i < N; i++) {
		cin >> x1 >> x2 >> y1 >> y2;
		edges[2*i]     = { true, x1, y1, y2 };
		edges[2*i + 1] = { false, x2, y1, y2 };
		Ys[2*i]        = y1;
		Ys[2*i + 1]    = y2;
	}
	sort(edges.begin(), edges.end());
	// optimize by removing duplicates
	Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());
	sort(Ys.begin(), Ys.end());

	SegTree segt(Ys.size());
	L = 0;
	S = 0;
	for (auto edge : edges) {
		S += L * (uint64_t)(edge.x - x_prev);
		x_prev = edge.x;
		segt.addRange(
			yCoordToIndex(edge.y1), yCoordToIndex(edge.y2),
			edge.isLeftEdge ? 1 : -1);
		L = segt.query();
	}

	cout << S << '\n';
	return 0;
}
