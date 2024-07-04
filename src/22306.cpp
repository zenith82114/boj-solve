/*
 * Q22306 - Small to large
 * Date: 2024.7.4
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100005;
array<int, MAXN> par, clr, cc, vis;
array<set<int>, MAXN> adj;
array<map<int, int>, MAXN> cnt;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q; q += n - 1;
    for (int x = 2; x <= n; ++x) {
        cin >> par[x];
        adj[par[x]].emplace(x);
        adj[x].emplace(par[x]);
    }
    for (int x = 1; x <= n; ++x) {
        cin >> clr[x];
        cc[x] = 0;
        ++cnt[0][clr[x]];
        vis[x] = -1;
    }
    int lst = 0;
    int cc_new = 1;

    while (q--) {
        int op, a; cin >> op >> a;
        a ^= lst;
        if (op&1) {
            stack<pair<int, int> > stk[2];
            vector<int> buf[2];

            adj[par[a]].erase(a);
            adj[a].erase(par[a]);
            stk[0].emplace(par[a], 0);
            stk[1].emplace(a, 0);

            while (stk[0].size() && stk[1].size()) for (int i : {0, 1}) {
                auto [x, p] = stk[i].top();
                vis[x] = q;
                if (!p) buf[i].emplace_back(x);
                auto it = adj[x].upper_bound(p);
                if (it == adj[x].end()) stk[i].pop();
                else {
                    int y = *it;
                    stk[i].top().second = y;
                    if (vis[y] != q) stk[i].emplace(y, 0);
                }
            }

            int cc_old = cc[a];
            auto& b = stk[0].empty()? buf[0] : buf[1];
            for (int x : b) {
                if (--cnt[cc_old][clr[x]] == 0) cnt[cc_old].erase(clr[x]);
                cc[x] = cc_new;
                ++cnt[cc_new][clr[x]];
            }
            ++cc_new;
        } else {
            cout << (lst = cnt[cc[a]].size()) << '\n';
        }
    }

    return 0;
}
