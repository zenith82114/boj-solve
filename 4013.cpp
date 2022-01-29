/*
 * Q4013 - DP on SCC reduction
 * Date: 2021.8.26
 */

#include<iostream>
#include<algorithm>
#include<bitset>
#include<set>
#include<vector>
using namespace std;

constexpr int maxN = 500000;
vector<int> graph[maxN + 1], graph_rev[maxN + 1],
graph_scc[maxN + 1];
int sccNo[maxN + 1];
int64_t cash_scc[maxN + 1], memo[maxN + 1];
bitset<maxN + 1> visited, restaurant_scc;

void dfs(int v, vector<int> &vec)
{
    visited.set(v);
    for (int& u : graph[v])
        if (!visited.test(u)) dfs(u, vec);
    vec.push_back(v);
}
void dfs_rev(int v, int n)
{
    visited.set(v);
    sccNo[v] = n;
    for (int& u : graph_rev[v])
        if (!visited.test(u)) dfs_rev(u, n);
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, S, P, x, y;
    vector<int> fin;
    int cN = 0;
    int64_t maxCash = 0;

    cin >> N >> M;
    while (M--) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph_rev[y].push_back(x);
    }

    for (int i = 1; i <= N; ++i)
        if (!visited.test(i)) dfs(i, fin);
    visited.reset();
    for (auto ri = fin.rbegin(); ri != fin.rend(); ++ri)
        if (!visited.test(*ri))
            dfs_rev(*ri, ++cN);
    for (int i = 1; i <= N; ++i) {
        int ci = sccNo[i], cj;
        vector<int>& g = graph_scc[ci];
        set<int> s;
        for (int& j : graph[i]) {
            if ((cj = sccNo[j]) != ci)
                s.insert(cj);
        }
        g.reserve(g.size() + distance(s.begin(), s.end()));
        g.insert(g.end(), s.begin(), s.end());
    }

    for (int i = 1; i <= N; ++i) {
        cin >> x;
        cash_scc[sccNo[i]] += x;
    }
    cin >> S >> P;
    while (P--) {
        cin >> x;
        restaurant_scc.set(sccNo[x]);
    }

    visited.reset();
    visited.set(sccNo[S]);
    for (int ci = sccNo[S]; ci <= cN; ++ci) {
        if (!visited.test(ci)) continue;
        memo[ci] += cash_scc[ci];
        if (restaurant_scc.test(ci))
            maxCash = max(maxCash, memo[ci]);
        for (const int& cj : graph_scc[ci]) {
            visited.set(cj);
            memo[cj] = max(memo[cj], memo[ci]);
        }
    }

    cout << maxCash << '\n';
    return 0;
}