/*
 * Q2261 - Closest point pair on 2D
 * Date: 2021.7.11
 */

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<climits>
using namespace std;
typedef pair<int, int> Point;
uint64_t sqrDist(Point &p, Point &q)
{
	return (uint64_t)pow(p.first - q.first, 2)
		+ pow(p.second - q.second, 2);
}
uint64_t minSqrDist(vector<Point> &V, int l, int r)
{
	uint64_t d2 = UINT64_MAX;
	if (r - l < 3) {
		for (int i = l; i < r; ++i)
			for (int j = i + 1; j <= r; ++j)
				d2 = min(d2, sqrDist(V[i], V[j]));
		return d2;
	}
	int m = (l + r) / 2;
	d2 = min(minSqrDist(V, l, m), minSqrDist(V, m + 1, r));
	if (!d2) return 0;
	int d = (int)ceil(sqrt(d2));
	vector<Point> W;
	int t = V[m].first - d;
	for (int i = m; i >= l; --i) {
		if (V[i].first > t)
			W.push_back(V[i]);
		else break;
	}
	t = V[m].first + d;
	for (int i = m + 1; i <= r; ++i) {
		if (V[i].first < t)
			W.push_back(V[i]);
		else break;
	}
	sort(W.begin(), W.end(), [](const Point &p, const Point &q)
	{return p.second < q.second; });
	int K = W.size();
	for (int i = 0; i < K; ++i) {
		for (int j = i + 1; j < K; ++j) {
			if (W[j].second - W[i].second >= d) break;
			d2 = min(d2, sqrDist(W[i], W[j]));
		}
	}
	return d2;
}
int main()
{
	ios::sync_with_stdio(0);
	int N; cin >> N;
	vector<Point> V;
	int x, y;
	for (int n = 0; n < N; ++n) {
		cin >> x >> y;
		V.push_back(Point(x, y));
	}
	sort(V.begin(), V.end());
	cout << minSqrDist(V, 0, N - 1) << endl;
}