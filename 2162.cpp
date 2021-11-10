/*
 * Q2162 - Line segment intersection and disjoint sets
 * Date: 2021.8.9
 */

#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;
constexpr int MAX = 3000;

struct Point { int x, y; };
struct Segment {
	Point p1, p2;
}segm[MAX];

int signof_crossprod
	(Point& Po, Point& Pi, Point& Pj)
{
	int	xi = Pi.x - Po.x, yi = Pi.y - Po.y,
		xj = Pj.x - Po.x, yj = Pj.y - Po.y;
	int A = xi * yj, B = xj * yi;
	return (A == B ? 0 : (A > B) ? 1 : -1);
}
bool intersects(int i, int j)
{
	Segment& Si = segm[i], & Sj = segm[j];
	int s1 = signof_crossprod(Si.p1, Si.p2, Sj.p1),
		s2 = signof_crossprod(Si.p1, Si.p2, Sj.p2),
		s3 = signof_crossprod(Sj.p1, Sj.p2, Si.p1),
		s4 = signof_crossprod(Sj.p1, Sj.p2, Si.p2);
	int L, M = 0, a[4];
	if (s1 != s2 && s3 != s4)
		return 1;
	else if (!(s1 || s2)) {
		if (Si.p1.y == Si.p2.y) {
			a[0] = Si.p1.x; a[1] = Si.p2.x;
			a[2] = Sj.p1.x; a[3] = Sj.p2.x;
		} else {
			a[0] = Si.p1.y; a[1] = Si.p2.y;
			a[2] = Sj.p1.y; a[3] = Sj.p2.y;
		}
		L = abs(a[0] - a[1]) + abs(a[2] - a[3]);
		for (int i = 0; i < 4; ++i)
			for (int j = i + 1; j < 4; ++j)
				M = max(M, abs(a[i] - a[j]));
		return L >= M;
	}
	else return 0;
}

struct Data {
	int parent, height, groupSize;
}db[MAX];
int leader(int x)
{
	int& p = db[x].parent;
	if (x == p) return p;
	return p = leader(p);
}
bool sameGroup(int x, int y)
{
	return leader(x) == leader(y);
}
int unite(int x, int y)
{
	int X = leader(x), Y = leader(y);
	Data& dX = db[X], & dY = db[Y];
	if (X == Y) return 0;
	int& hX = dX.height, & hY = dY.height;
	if (hX < hY) {
		dX.parent = Y;
		return dY.groupSize += dX.groupSize;
	} else {
		dY.parent = X;
		if (hX == hY) hX++;
		return dX.groupSize += dY.groupSize;
	}
}
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, n, m;
	int nG, maxGsize = 1;
	Segment* s;

	cin >> N; nG = N;
	for (n = 0; n < N; ++n) {
		db[n].parent = n;
		db[n].height = 0;
		db[n].groupSize = 1;
		s = &segm[n];
		cin >> s->p1.x >> s->p1.y
			>> s->p2.x >> s->p2.y;
		for (m = 0; m < n; ++m) {
			if (!sameGroup(m, n) && intersects(m, n)) {
				nG--;
				maxGsize = max(maxGsize, unite(m, n));
			}
		}
	}
	cout << nG << '\n' << maxGsize;

	return 0;
}