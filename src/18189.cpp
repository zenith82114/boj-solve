/*
 * Q18189 - Euler tour + Binary search
 * Date: 2023.5.8
 */

#include<bits/stdc++.h>
using namespace std;

int tag[250001], par[250001];
vector<int> adj[250001], tpos[250001];
pair<int, int> eut[250001];
int clk = 0;

void dfs(int px, int x) {
    par[x] = px;
    eut[x].first = clk;
    tpos[tag[x]].emplace_back(clk);
    for (int y : adj[x]) if (y != px) ++clk, dfs(x, y);
    eut[x].second = clk;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    for (int i = 0; i < N; cin >> tag[++i]);
    for (int i = 1; i < N; ++i) {
        int x, y; cin >> x >> y;
        if (tag[x] == tag[y]) { cout << "0\n0\n0"; return 0; }
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }

    dfs(0, 1);

    auto f = [&] (int x, int a) {
        auto& v = tpos[a];
        auto& [l, r] = eut[x];
        return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
    };

    vector<int> pfs(N+1);

    for (int x = 1; x <= N; ++x) for (int y : adj[x]) {
        if (x == par[y] && f(y, tag[x]) > 0) {
            auto& [l, r] = eut[y];
            pfs[0]++; pfs[l]--; pfs[r+1]++;
        } else if (y == par[x] && (long)tpos[tag[x]].size() > f(x, tag[x])) {
            auto& [l, r] = eut[x];
            pfs[l]++; pfs[r+1]--;
        }
    }
    partial_sum(pfs.begin(), pfs.end(), pfs.begin());

    int p1 = 0; int64_t p2 = 0, p3 = 0;
    for (int x = 1; x <= N; ++x) if (!pfs[eut[x].first])
        p1++, p2 += x, p3 += (int64_t)x * x;
    cout << p1 << '\n' << p2 << '\n' << p3;
    return 0;
}
