/*
 * Q24599 - Greedy + 2-SAT
 * Date: 2023.4.4
 */

#include<bits/stdc++.h>
using namespace std;

int clk = 0;
int scc_id = 0;
int entry[200], link[200], scc[200];
vector<int> adj[200];
stack<int> st;
bool on_st[200];

void dfs(int u) {
    entry[u] = link[u] = ++clk;
    st.emplace(u); on_st[u] = true;
    for (const int& v : adj[u]) {
        if (!entry[v]) {
            dfs(v);
            link[u] = min(link[u], link[v]);
        }
        else if (on_st[v])
            link[u] = min(link[u], entry[v]);
    }
    if (entry[u] == link[u]) {
        ++scc_id;
        while (st.top() != u) {
            int v = st.top();
            st.pop(); on_st[v] = false;
            scc[v] = scc_id;
        }
        st.pop(); on_st[u] = false;
        scc[u] = scc_id;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;
    while (N--) {
        string s; cin >> s;
        for (int i = 0;   i < K; ++i) if (s[i] != 'X')
        for (int j = i+1; j < K; ++j) if (s[j] != 'X') {
            int ui = i<<1 ^ (s[i] == 'F');
            int uj = j<<1 ^ (s[j] == 'F');
            adj[ui].emplace_back(uj ^ 1);
            adj[uj].emplace_back(ui ^ 1);
        }
    }

    const auto test = [&] (void) {
        clk = 0;
        scc_id = 0;
        memset(entry, 0, sizeof entry);
        memset(link, 0, sizeof link);
        memset(scc, 0, sizeof scc);
        for (int i = 0; i < 2*K; ++i) if (!scc[i]) dfs(i);
        for (int i = 0; i < K; ++i)
            if (scc[i<<1] == scc[i<<1|1]) return false;
        return true;
    };

    if (!test()) { cout << -1; return 0; }

    for (int i = 0; i < K; ++i) {
        int t = i<<1, f = t^1;
        adj[t].emplace_back(f);
        if (test()) cout << 'F';
        else {
            adj[t].pop_back();
            adj[f].emplace_back(t);
            cout << 'T';
        }
    }

    return 0;
}
