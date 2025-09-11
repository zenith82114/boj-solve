/*
 * Q14832 - bipartite matching, two pointers
 * Date: 2025.9.11
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 50'000, MAXV = 1e6 + 4;

int a[6*MAXN];
vector<int> g[MAXV];
int clk = 0, vis[MAXV];
int mx[MAXV], my[MAXN], msz;

int augment(int x) {
    vis[x] = clk;
    for (int y : g[x]) {
        int z = my[y];
        if (z == -1 || (vis[z] != clk && augment(z))) {
            mx[x] = y;
            my[y] = x;
            return 1;
        }
    }
    return 0;
}

void expand(int x) {
    ++clk;
    msz += augment(x);
}

void shrink(int x) {
    int y = mx[x];
    if (y != -1) {
        mx[x] = my[y] = -1;
        --msz;
    }
    g[x].clear();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    memset(mx, -1, sizeof mx);
    memset(my, -1, sizeof my);

    int TC; cin >> TC;
    for (int tc = 1; tc <= TC; ++tc) {
        int n; cin >> n;
        for (int y = 0; y < n; ++y)
        for (int i = 0; i < 6; ++i) {
            int& x = a[6*y + i]; cin >> x;
            g[x].emplace_back(y);
        }
        sort(a, a + 6*n);
        const int nn = distance(a, unique(a, a + 6*n));

        int ans = 0;
        msz = 0;
        int s = 0, e = 0;
        for (; e < nn; ++e) {
            expand(a[e]);
            while (msz < e - s + 1) { shrink(a[s++]); expand(a[e]); }
            ans = max(ans, msz);
            if (e + 1 < nn && a[e] + 1 < a[e + 1]) while (s <= e) shrink(a[s++]);
        }
        for (; s < nn; ++s) shrink(a[s]);

        cout << "Case #" << tc << ": " << ans << '\n';
    }

    return 0;
}
