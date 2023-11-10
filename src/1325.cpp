/*
 * Q1325 - SCC + topological sorting
 * Date: 2023.11.10
 */

#include<bits/stdc++.h>
using namespace std;

#define SIZE 16384

vector<int> adj[SIZE];
int clk = 0;
int entry[SIZE] {}, link[SIZE];
stack<int> st;
bool on_st[SIZE] {};
int scc[SIZE] {};
int scc_id = 0;

vector<int> adjc[SIZE];
int in_deg[SIZE] {};
bitset<SIZE> mask[SIZE];
int wei[SIZE] {};
int wei_sum[SIZE] {};

void dfs(int x) {
    clk++;
    entry[x] = clk;
    link[x] = clk;
    st.emplace(x); on_st[x] = true;
    for (int y : adj[x]) {
        if (!entry[y]) {
            dfs(y);
            link[x] = min(link[x], link[y]);
        }
        else if (on_st[y])
            link[x] = min(link[x], entry[y]);
    }
    if (entry[x] == link[x]) {
        scc_id++;
        while (st.top() != x) {
            int y = st.top();
            st.pop(); on_st[y] = false;
            scc[y] = scc_id;
        }
        st.pop(); on_st[x] = false;
        scc[x] = scc_id;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
    }
    for (int x = 1; x <= n; ++x) if (!entry[x]) dfs(x);
    for (int x = 1; x <= n; ++x) for (int y : adj[x]) {
        if (scc[x] != scc[y])
            adjc[scc[x]].emplace_back(scc[y]);
    }

    int cn = scc_id;
    for (int x = 1; x <= cn; ++x) {
        auto& v = adjc[x];
        for (int y : v) ++in_deg[y];
    }

    queue<int> q;
    for (int x = 1; x <= cn; ++x) if (!in_deg[x]) q.emplace(x);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        mask[x].set(x);
        for (int y : adjc[x]) {
            mask[y] |= mask[x];
            if (--in_deg[y] == 0) q.emplace(y);
        }
    }

    for (int x = 1; x <= n; ++x) ++wei[scc[x]];
    m = 0;
    for (int x = 1; x <= cn; ++x) {
        for (int y = 1; y <= cn; ++y) if (mask[x].test(y))
            wei_sum[x] += wei[y];
        m = max(m, wei_sum[x]);
    }
    for (int x = 1; x <= n; ++x) if (wei_sum[scc[x]] == m) cout << x << ' ';
    return 0;
}
