/*
 * Q2213 - Tree DP
 * Date: 2023.4.22
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> tree[10001];
int sum[10001][2];
bool opt[10001];

void dfs1(int pu, int u) {
    for (int v : tree[u]) if (v != pu) {
        dfs1(u, v);
        sum[u][0] += max(sum[v][0], sum[v][1]);
        sum[u][1] += sum[v][0];
    }
}

void dfs2(int pu, int u) {
    opt[u] = !opt[pu] && sum[u][0] < sum[u][1];
    for (int v : tree[u]) if (v != pu) dfs2(u, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) cin >> sum[i][1];

    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    dfs1(0, 1);
    cout << max(sum[1][0], sum[1][1]) << '\n';
    dfs2(0, 1);
    for (int i = 1; i <= N; ++i) if (opt[i]) cout << i << ' ';

    return 0;
}
