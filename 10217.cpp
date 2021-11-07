/*
 * Q10217 - Dijkstra's + DP
 * Date: 2021.7.22
 */

#include<iostream>
#include<limits>
#include<queue>
#include<tuple>
#include<algorithm>
using namespace std;

typedef tuple<int, int, int> Info;
struct PQcmp {
	bool operator()(const Info& a, const Info& b) {
		return get<2>(a) > get<2>(b);
	}
};

const int INF = numeric_limits<int>::max();
vector<vector<Info>> adj;
int dp[100][10001];

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int TC;
	int N, M, K, u, v, c, d, r;
	int c_old, d_old, c_new, d_new;

	cin >> TC;
	while (TC--) {
		cin >> N >> M >> K;
		adj.clear(); adj.resize(N);
		while (K--) {
			cin >> u >> v >> c >> d;
			adj[--u].emplace_back(--v, c, d);
		}
		fill_n(dp[0], M + 1, 0);
		for (int n = 1; n < N;
			fill_n(dp[n++], M + 1, INF));

		priority_queue<Info, vector<Info>, PQcmp> PQ;
		PQ.emplace(0, 0, 0);
		while (!PQ.empty()) {
			tie(u, c_old, d_old) = PQ.top(); PQ.pop();
			if (dp[u][c_old] < d_old) continue;
			for (const auto& vcd : adj[u]) {
				tie(v, c, d) = vcd;
				c_new = c_old + c;
				d_new = d_old + d;
				for (c = c_new; c <= M && dp[v][c] > d_new;
					dp[v][c++] = d_new);
				if (c > c_new)
					PQ.emplace(v, c_new, d_new);
			}
		}
		r = dp[N - 1][M];
		if (r == INF) cout << "Poor KCM\n";
		else cout << r << '\n';
	}

	return 0;
}