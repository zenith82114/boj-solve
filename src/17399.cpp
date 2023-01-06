/*
 * Q17399 - LCA
 * Date: 2023.1.6
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> tree, par;
vector<int> dep;
int lgN;

void dfs(int pu, int u) {
    dep[u] = dep[pu] + 1;
    par[0][u] = pu;
    for (const int& v : tree[u]) if (v != pu)
        dfs(u, v);
}

int dist(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int ans = dep[u] - dep[v];
    for (int d = ans, i = 0; d; d >>= 1, ++i) if (d & 1)
        u = par[i][u];
    if (u != v) {
        for (int i = lgN; ~i; --i) if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
            ans += (1<<i)*2;
        }
        ans += 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    tree.resize(N+1);
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    lgN = [](int n) {
        int k = 0;
        for (; n > 1; n >>= 1) ++k;
        return k;
    }(N);
    dep.resize(N+1);
    par.resize(lgN+1, vector<int>(N+1));
    dfs(0, 1);

    for (int i = 1; i <= lgN; ++i)
    for (int u = 1; u <= N; ++u)
        par[i][u] = par[i-1][par[i-1][u]];

    int Q; cin >> Q;
    while (Q--) {
        int A, B, C; cin >> A >> B >> C;
        int AB = dist(A, B);
        int AC = dist(A, C);
        int BC = dist(B, C);
        if ((AB | AC | BC) & 1) {
            cout << "-1\n";
            continue;
        }

        int X = AB ^ AC ^ BC;
        if (X == AB) {
            swap(A, C);
            swap(AB, BC);
        }
        else if (X == AC) {
            swap(A, B);
            swap(AC, BC);
        }
        else if (X != BC) {
            cout << "-1\n";
            continue;
        }

        if (AB >= BC) {
            int M = dep[A] < dep[B]? B : A;
            for (int d = AB/2, i = 0; d; d >>= 1, ++i) if (d & 1)
                M = par[i][M];
            cout << M << '\n';
        }
        else
            cout << "-1\n";
    }

    return 0;
}
