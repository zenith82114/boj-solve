/*
 * Q2618 - DP
 * Date: 2021.7.26
 */

#include<iostream>
#include<algorithm>
using namespace std;
typedef pair<int, int> Coord;
constexpr auto call_1 = true, call_2 = false;

int dp[1001][1001];
Coord pos[1001];
bool call[1001][1001];
inline int dist(Coord& a, Coord& b)
{
	return abs(a.first - b.first) + abs(a.second - b.second);
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);

	int N, W;
	int i, j, k, dp1, dp2;
	Coord pos_i, pos_j;

	cin >> N >> W;
	for (int w = 1; w <= W; ++w) {
		cin >> i >> j;
		pos[w] = make_pair(i, j);
	}
	
	fill_n(dp[W], W + 1, 0);
	for (i = W - 1; i >= 0; --i) {
		dp[i][W] = 0;
		pos_i = i ? pos[i] : make_pair(1, 1);
		for (j = W - 1; j >= 0; --j) {
			if (i && i == j) continue;
			pos_j = j ? pos[j] : make_pair(N, N);
			k = max(i, j) + 1;
			dp1 = dist(pos_i, pos[k]) + dp[k][j];
			dp2 = dist(pos_j, pos[k]) + dp[i][k];
			if (dp1 < dp2) {
				dp[i][j] = dp1;
				call[i][j] = call_1;
			} else {
				dp[i][j] = dp2;
				call[i][j] = call_2;
			}
		}
	}
	cout << dp[0][0] << '\n';
	i = j = 0; k = 1;
	while (i < W && j < W) {
		if (call[i][j] == call_1) {
			cout << "1\n";
			i = k++;
		} else {
			cout << "2\n";
			j = k++;
		}
	}

	return 0;
}