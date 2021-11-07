/*
 * Q2213 - Maximum independent set on a tree
 * Date: 2021.8.7
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
constexpr int MAX = 10000;

vector<int> adj[MAX + 1];
int weight[MAX + 1], dp[MAX + 1][2];

pair<vector<int>, vector<int>> max_indep_sum(int v, int pv)
{
	vector<int> set_vInc = { v }, set_vExc;
	int& size_vInc = dp[v][0], & size_vExc = dp[v][1];
	size_vInc += weight[v];

	for (int& u : adj[v]) {
		if (u == pv) continue;
		auto p = max_indep_sum(u, v);
		auto& set_uInc = p.first, & set_uExc = p.second;
		int& size_uInc = dp[u][0], & size_uExc = dp[u][1];
		set_vInc.insert(set_vInc.end(), set_uExc.begin(), set_uExc.end());
		size_vInc += size_uExc;
		if (size_uInc > size_uExc) {
			set_vExc.insert(set_vExc.end(), set_uInc.begin(), set_uInc.end());
			size_vExc += size_uInc;
		} else {
			set_vExc.insert(set_vExc.end(), set_uExc.begin(), set_uExc.end());
			size_vExc += size_uExc;
		}
	}
	return { set_vInc,set_vExc };
}
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, u, v, n;

	cin >> N;
	for (n = 1; n <= N;
		cin >> weight[n++]);
	for (n = 1; n < N; ++n) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	auto p = max_indep_sum(1, 0);
	auto& p0 = p.first, & p1 = p.second;
	cout << max(dp[1][0], dp[1][1]) << '\n';
	if (dp[1][0] > dp[1][1]) {
		sort(p0.begin(), p0.end());
		for (int& i : p0)
			cout << i << ' ';
	} else {
		sort(p1.begin(), p1.end());
		for (int& i : p1)
			cout << i << ' ';
	}

	return 0;
}