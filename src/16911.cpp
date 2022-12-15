/*
 * Q16911 - Offline dynamic connectivity
 * Date: 2022.2.23
 */

#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

struct EdgeTime {
    int u, v, ts, te;
    EdgeTime(int u, int v, int ts, int te)
    : u(u), v(v), ts(ts), te(te) {};
};
vector<EdgeTime> edti;
map<pii, int> mp;
vector<pii> que;

// Union-find
vector<int> par, rnk;
int find(int x) {
    while (x != par[x])
        x = par[x];
    return x;
}
bool connected(int x, int y) {
    return find(x) == find(y);
}
int link(int x, int y) {
    int X = find(x), Y = find(y);
    if (X == Y)
        return 0;
    if (rnk[X] < rnk[Y]) {
        par[X] = Y;
        return X;
    }
    else {
        par[Y] = X;
        if (rnk[X] == rnk[Y]) {
            rnk[X]++;
            return -Y;
        }
        return Y;
    }
}
void rollback(int z) {
    if (!z)
        return;
    if (z < 0) {
        z = -z;
        rnk[par[z]]--;
    }
    par[z] = z;
}

// DnC
vector<vector<pii>> E;
inline int lc(int n) { return n<<1; }
inline int rc(int n) { return n<<1|1; }
void add_util(int n, int l, int r, EdgeTime& e) {
    int m = (l+r)>>1;
    if (l > e.te || r < e.ts)
        return;
    if (l < e.ts || r > e.te) {
        add_util(lc(n), l, m, e);
        add_util(rc(n), m+1, r, e);
    }
    else E[n].emplace_back(e.u, e.v);
}
void solve_util(int n, int l, int r) {
    vector<int> log;
    int m = (l+r)>>1;
    for (pii& e : E[n])
        log.emplace_back(link(e.first, e.second));
    if (l != r) {
        solve_util(lc(n), l, m);
        solve_util(rc(n), m+1, r);
    }
    else cout << connected(que[l].first, que[l].second) << '\n';
    for (auto rit = log.rbegin(); rit != log.rend(); ++rit)
        rollback(*rit);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    int Q = 0;
    while (M--) {
        int t, u, v; cin >> t >> u >> v;
        if (u > v)
            swap(u, v);
        if (t == 1)
            mp[{u, v}] = Q;
        else if (t == 2) {
            if (mp[{u, v}] < Q)
                edti.emplace_back(u, v, mp[{u, v}], Q-1);
            mp.erase({u, v});
        }
        else {
            que.emplace_back(u, v);
            Q++;
        }
    }
    for (const auto& [k, v] : mp)
        edti.emplace_back(k.first, k.second, v, Q-1);

    E.resize(2 * [](int n) {
        if (n & (n-1)) {
            for (int i = 1; i < 32; i <<= 1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }(Q));
    for (auto& e : edti)
        add_util(1, 0, Q-1, e);

    par.resize(N+1), rnk.resize(N+1, 0);
    iota(par.begin(), par.end(), 0);
    solve_util(1, 0, Q-1);

    return 0;
}
