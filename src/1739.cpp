
/*
 * Q1739 - 2-SAT
 * Date: 2023.1.16
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[4096];
int clk;
int entry[4096], link[4096];
stack<int> st;
bool on_st[4096];
int scc[4096];
int scc_id;

void tarjan(int u) {
    clk++;
    entry[u] = clk;
    link[u] = clk;
    st.emplace(u); on_st[u] = true;
    for (const int& v : adj[u]) {
        if (!entry[v]) {
            tarjan(v);
            link[u] = min(link[u], link[v]);
        }
        else if (on_st[v])
            link[u] = min(link[u], entry[v]);
    }
    if (entry[u] == link[u]) {
        scc_id++;
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
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M, K; cin >> N >> M >> K;
        const int U = N + M;
        const auto neg = [U] (int x) {
            return 2*U + 1 - x;
        };
        const auto add_clause = [&neg] (int x, int y) {
            adj[neg(y)].emplace_back(x);
            adj[neg(x)].emplace_back(y);
        };

        for (int u = 1; u <= 2*U; ++u) adj[u].clear();

        bitset<4096> used;
        while (K--) {
            int a, b, c, d; cin >> a >> b >> c >> d;
            b += N;
            d += N;
            used.set(a); used.set(neg(a));
            used.set(b); used.set(neg(b));
            used.set(c); used.set(neg(c));
            used.set(d); used.set(neg(d));
            int na = b < d? a : neg(a);
            int nb = a < c? b : neg(b);
            int nc = b < d? c : neg(c);
            int nd = a < c? d : neg(d);
            if (a == c && b != d) add_clause(na, na);
            else
            if (a != c && b == d) add_clause(nb, nb);
            else
            if (a != c && b != d) {
                add_clause(na, nb);
                add_clause(na, nc);
                add_clause(nd, nb);
                add_clause(nd, nc);
            }
        }

        clk = 0;
        scc_id = 0;
        memset(entry, 0, sizeof entry);
        memset(scc, 0, sizeof scc);
        for (int u = 1; u <= 2*U; ++u) if (used[u] && !entry[u])
            tarjan(u);

        bool test = true;
        for (int u = 1; u <= U; ++u) if (used[u] && scc[u] == scc[neg(u)]) {
            test = false; break;
        }
        cout << (test? "Yes\n" : "No\n");
    }

    return 0;
}
