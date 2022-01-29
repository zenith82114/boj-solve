/*
 * Q1949 - Tree DP
 * Date: 2021.8.9
 * 
 * Maximize the sum of "colored" nodes under these rules:
 * 1. A colored node must not have a colored neighbor.
 * 2. Every uncolored node must have at least one colored neighbor.
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
constexpr int MAX = 10000;

vector<int> adj[MAX + 1];
int W[MAX + 1], dp[MAX + 1][4];

// dp[v][i] = max colored sum of subtree(v)...
// i = 0: when v is colored
// i = 1: when v is not colored and has at least one colored child
// i = 2: when v and all of its children are not colored
// i = 3: max of the above

void dfs(int v, int pv)
{
    int v0 = W[v], v1 = 0, v2 = 0;
    int M = 0;
    for (int& u : adj[v]) {
        if (u != pv) {
            dfs(u, v);
            v0 += max(dp[u][1], dp[u][2]);
            v2 += dp[u][1];
            M += dp[u][3];
        }
    }
    for (int& u : adj[v]) {
        if (u != pv)
            v1 = max(v1, M - dp[u][3] + dp[u][0]);
    }
    dp[v][0] = v0; dp[v][1] = v1; dp[v][2] = v2;
    dp[v][3] = max({v0, v1, v2});
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, n, u, v;

    cin >> N;
    for (n = 1; n <= N; cin >> W[n++]);
    for (n = 1; n < N; ++n) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << dp[1][3];
    
    return 0;
}