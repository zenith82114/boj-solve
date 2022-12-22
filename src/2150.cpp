/*
 * Q2150 - Tarjan's SCC alg.
 * Date: 2022.12.22
 */

#include<bits/stdc++.h>
using namespace std;

int clk = 0;
vector<vector<int>> adj;
vector<int> entry, link;
stack<int> st;
vector<bool> on_st;
vector<vector<int>> sccs;

void tarjan(int u) {
    clk++;
    entry[u] = clk;
    link[u] = clk;
    st.push(u); on_st[u] = true;
    for (const int& v : adj[u]) {
        if (!entry[v]) {
            tarjan(v);
            link[u] = min(link[u], link[v]);
        }
        else if (on_st[v])
            link[u] = min(link[u], entry[v]);
    }
    if (entry[u] == link[u]) {
        vector<int> scc;
        while (st.top() != u) {
            int v = st.top();
            st.pop(); on_st[v] = false;
            scc.emplace_back(v);
        }
        st.pop(); on_st[u] = false;
        scc.emplace_back(u);
        sccs.emplace_back(scc);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int V, E; cin >> V >> E;
    adj.resize(V+1);
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
    }

    entry.resize(V+1, 0);
    link.resize(V+1);
    on_st.resize(V+1, false);

    for (int u = 1; u <= V; ++u) if (!entry[u]) tarjan(u);

    for (auto& scc : sccs) sort(scc.begin(), scc.end());
    sort(sccs.begin(), sccs.end());

    cout << sccs.size() << '\n';
    for (const auto& scc : sccs) {
        for (const auto& u : scc) cout << u << ' ';
        cout << "-1\n";
    }

    return 0;
}
