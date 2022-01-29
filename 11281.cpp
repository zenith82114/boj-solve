/*
 * Q11281 - 2-SAT using SCC
 * Date: 2021.8.27
 */

#include<iostream>
#include<bitset>
#include<vector>
using namespace std;

constexpr int maxN = 10000, RANGE = (maxN << 1) + 1;
vector<int> graph[RANGE], graph_rev[RANGE];
bitset<RANGE> visited;
int sccNo[RANGE];

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
    int N, DN, M, i, j, ni, nj;
    vector<int> F;
    int cN = 0;
    bool sol[maxN + 1];

    cin >> N >> M;
    DN = N << 1;
    while (M--) {
        cin >> i >> j;
        if (i < 0) i += DN + 1;
        if (j < 0) j += DN + 1;
        ni = DN - i + 1;
        nj = DN - j + 1;
        graph[ni].push_back(j);
        graph[nj].push_back(i);
        graph_rev[i].push_back(nj);
        graph_rev[j].push_back(ni);
    }

    for (i = 1; i <= DN; ++i)
        if (!visited.test(i)) dfs(i, F);
    visited.reset();
    for (auto rf = F.rbegin(); rf != F.rend(); ++rf)
        if (!visited.test(*rf))
            dfs_rev(*rf, ++cN);

    for (i = 1, ni = DN; i <= N; ++i, --ni) {
        if (sccNo[i] == sccNo[ni]) {
            cout << 0;
            return 0;
        }
        else sol[i] = (sccNo[ni] < sccNo[i]);
    }
    cout << "1\n";
    for (i = 1; i <= N; ++i)
        cout << sol[i] << ' ';

    return 0;
}