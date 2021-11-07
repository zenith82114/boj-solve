/*
 * Q2887 - Minimal spanning tree w/ custom weight function
 * Date: 2021.8.2
 */

#include<iostream>
#include<algorithm>
#include<numeric>
#include<queue>
#include<tuple>
using namespace std;
constexpr int MAX = 100000;

struct Point {
	int id, pos[3];
}points[MAX];
bool(*PointCmp[3])(const Point&, const Point&) = {
	[](const Point& p1, const Point& p2) {
		return p1.pos[0] < p2.pos[0]; },
	[](const Point& p1, const Point& p2) {
		return p1.pos[1] < p2.pos[1]; },
	[](const Point& p1, const Point& p2) {
		return p1.pos[2] < p2.pos[2]; }
};

struct PQitem {
	int I, J, D;
	PQitem(int i, int j, int d)
		:I(i), J(j), D(d) {};
	bool operator<(const PQitem& that) const {
		return this->D > that.D;
	};
};
priority_queue<PQitem> PQ;

int parent[MAX], height[MAX];
int leader(int x)
{
	int& p = parent[x];
	if (p == x) return p;
	return p = leader(p);
}
bool unite(int x, int y)
{
	int X = leader(x), Y = leader(y);
	if (X == Y) return 0;
	int& hX = height[X], & hY = height[Y];
	if (hX < hY)
		parent[X] = Y;
	else {
		parent[Y] = X;
		if (hX == hY) hX++;
	}
	return 1;
}
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);

	int N;
	int T, i, j, d;
	long long S = 0;

	cin >> N;
	iota(parent, parent + N, 0);
	fill_n(height, N, 0);
	for (i = 0; i < N; ++i) {
		Point& P = points[i];
		P.id = i;
		cin >> P.pos[0] >> P.pos[1] >> P.pos[2];
	}
	for (i = 0; i < 3; ++i) {
		sort(points, points + N, PointCmp[i]);
		for (j = 1; j < N; ++j) {
			Point& P1 = points[j], & P2 = points[j - 1];
			PQ.emplace(P1.id, P2.id, P1.pos[i] - P2.pos[i]);
		}
	}
	T = N - 1;
	while (T) {
		const PQitem& it = PQ.top();
		tie(i, j, d) = make_tuple(it.I, it.J, it.D);
		PQ.pop();
		if (unite(i, j)) {
			T--; S += d;
		}
	}
	cout << S;

	return 0;
}