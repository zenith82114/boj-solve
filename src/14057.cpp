/*
 * Q14057 - Monotone stack + tree
 * Date: 2024.1.9
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<int> > chd;
vector<int> par, hei;

void dfs(int x) {
    for (int y : chd[x]) {
        dfs(y);
        hei[x] = max(hei[x], hei[y]);
    }
    ++hei[x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k; cin >> n >> k;
    vector<int> h(n); for (int& hi : h) cin >> hi;
    auto sh(h);
    sh.emplace_back(0);
    sort(sh.begin(), sh.end());

    chd.resize(n+1);
    par.resize(n+1);
    int cur = 0;
    for (int hi : h) {
        int x = lower_bound(sh.begin(), sh.end(), hi) - sh.begin();
        while (0 < cur && cur < x) {
            cur = par[cur];
        }
        chd[cur].emplace_back(x);
        par[x] = cur;
        cur = x;
    }
    hei.resize(n+1); dfs(0);
    for (int x = 2; x <= n; ++x) hei[x] = max(hei[x], hei[x-1]);

    while (k--) {
        int t; cin >> t;
        if (t < sh[1]) cout << "0 ";
        else {
            int x = lower_bound(sh.begin(), sh.end(), t) - sh.begin();
            cout << hei[x-1] << ' ';
        }
    }

    return 0;
}
