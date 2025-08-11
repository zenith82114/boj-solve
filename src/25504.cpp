/*
 * Q25504 - Regions trick
 * Date: 2025.8.12
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 50'004, inf = 0x3f3f3f3f;

vector<pair<int, int> > g[MAXN];
int temp[MAXN];
vector<int> ppc[MAXN];
map<pair<int, int>, int> cache;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q; cin >> n >> m >> q;
    const int k = round(cbrt(2. * m * m / (q * log2(m + 1))) + .5);
    while (m--) {
        int x, y, t; cin >> x >> y >> t;
        g[x].emplace_back(y, t);
        g[y].emplace_back(x, t);
    }
    for (auto& gx : g) sort(begin(gx), end(gx));
    auto heavy = [&k](int x) { return (int)g[x].size() > k; };

    memset(temp, inf, sizeof temp);
    for (int x = 1; x <= n; ++x) if (heavy(x)) {
        temp[x] = 0;
        for (auto [y, t] : g[x]) temp[y] = t;
        ppc[x].reserve(n + 1);
        ppc[x].insert(end(ppc[x]), temp, temp + n + 1);
        for (auto [y, _] : g[x]) for (auto [v, t] : g[y]) {
            ppc[x][v] = min(ppc[x][v], temp[y] + t);
        }
        temp[x] = inf;
        for (auto [y, _] : g[x]) temp[y] = inf;
    }

    while (q--) {
        int x, y; cin >> x >> y;
        if (make_pair(g[x].size(), x) < make_pair(g[y].size(), y)) swap(x, y);

        auto key = make_pair(x, y);
        if (cache.find(key) == end(cache)) {
            int ans = inf;
            if (heavy(x)) {
                ans = ppc[x][y];
                for (auto [v, t] : g[y]) ans = min(ans, ppc[x][v] + t);
            } else {
                for (auto [u, t1] : g[x]) for (auto [v, t2] : g[y]) {
                    if (u == y) ans = min(ans, t1);
                    if (v == x) ans = min(ans, t2);
                    if (u == v) ans = min(ans, t1 + t2);
                    auto lb = lower_bound(begin(g[u]), end(g[u]), make_pair(v, 0));
                    if (lb != end(g[u]) && lb->first == v) ans = min(ans, t1 + lb->second + t2);
                }
            }
            cache.emplace(key, ans < inf? ans : -1);
        }
        cout << cache[key] << '\n';
    }

    return 0;
}
