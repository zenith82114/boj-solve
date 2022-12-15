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
int scc_id[RANGE];

void dfs(int v, vector<int> &vec) {
    visited.set(v);
    for (int& u : graph[v])
        if (!visited.test(u)) dfs(u, vec);
    vec.push_back(v);
}
void dfs_rev(int v, int n) {
    visited.set(v);
    scc_id[v] = n;
    for (int& u : graph_rev[v])
        if (!visited.test(u)) dfs_rev(u, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    int DN = N << 1;
    while (M--) {
        int i, j; cin >> i >> j;
        if (i < 0) i += DN + 1;
        if (j < 0) j += DN + 1;
        int ni = DN - i + 1;
        int nj = DN - j + 1;
        graph[ni].push_back(j);
        graph[nj].push_back(i);
        graph_rev[i].push_back(nj);
        graph_rev[j].push_back(ni);
    }

    vector<int> F;
    for (int i = 1; i <= DN; ++i)
        if (!visited.test(i)) dfs(i, F);
    visited.reset();
    int cN = 0;
    for (auto rf = F.rbegin(); rf != F.rend(); ++rf)
        if (!visited.test(*rf))
            dfs_rev(*rf, ++cN);

    bool sol[maxN +1];
    for (int i = 1, ni = DN; i <= N; ++i, --ni) {
        if (scc_id[i] == scc_id[ni]) {
            cout << "0\n";
            return 0;
        }
        else sol[i] = (scc_id[ni] < scc_id[i]);
    }
    cout << "1\n";
    for (int i = 1; i <= N; ++i)
        cout << sol[i] << ' ';
    cout << '\n';

    return 0;
}
