/*
 * Q32395 - sqrt decomposition
 * Date: 2025.8.10
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e5 + 4;
constexpr int MOD = 1e9 + 7;

vector<pair<int, int> > edges;
int deg[MAXN];
vector<int> g[MAXN][2];
bitset<MAXN> heavy, mark;
int cnt[MAXN];

enum CycleType {
    LLLL=0,
    HLLL,
    HHLL,
    HLHL,
    HHHL,
    HHHH
};
i64 acc[6];
constexpr int mult[] { 4, 1, 2, 2, 2, 4 };

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    const int k = round(sqrt(n + m) + .5);
    while (m--) {
        int x, y; cin >> x >> y;
        edges.emplace_back(x, y);
        ++deg[x]; ++deg[y];
    }
    for (int x = 1; x <= n; ++x) if (deg[x] >= k) heavy.set(x);
    for (auto [x, y] : edges) {
        g[x][heavy[y]].emplace_back(y);
        g[y][heavy[x]].emplace_back(x);
    }

    for (int x = 1; x <= n; ++x) {
        if (heavy[x]) {
            for (int y : g[x][0]) mark.set(y);
            for (int y : g[x][1]) mark.set(y);
            for (int z = 1; z <= n; ++z) if (z != x) {
                i64 nl = 0, nh = 0;
                for (int w : g[z][0]) if (mark[w]) ++nl;
                for (int w : g[z][1]) if (mark[w]) ++nh;
                if (heavy[z]) {
                    acc[HLHL] += nl * (nl - 1) / 2;
                    acc[HHHL] += nl * nh;
                    acc[HHHH] += nh * (nh - 1) / 2;
                } else {
                    acc[HLLL] += nl * (nl - 1) / 2;
                    acc[HHLL] += nl * nh;
                }
            }
            for (int y : g[x][0]) mark.reset(y);
            for (int y : g[x][1]) mark.reset(y);
        } else {
            for (int y : g[x][0])
            for (int z : g[y][0]) if (z != x) acc[LLLL] += cnt[z]++;
            for (int y : g[x][0])
            for (int z : g[y][0]) if (z != x) --cnt[z];
        }
    }

    i64 ans = 0;
    for (int i = 0; i < 6; ++i) ans += acc[i] / mult[i];
    cout << (ans % MOD);
    return 0;
}
