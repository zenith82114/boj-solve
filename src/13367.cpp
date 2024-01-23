/*
 * Q13367 - Stoer-Wagner alg.
 * Date: 2024.1.23
 */

#include<bits/stdc++.h>
using namespace std;

int wei[512][512];
int f[512];
bitset<512> live, seen;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc; while (tc--) {
        int n, m; cin >> n >> m;
        if (n == 1) { cout << 0; continue; }

        for (int x = 1; x <= n; ++x) {
            fill_n(wei[x] + 1, n, 0);
        }
        while (m--) {
            int x, y, w; cin >> x >> y >> w;
            wei[x][y] += w;
            wei[y][x] += w;
        }

        live.set();
        int ans = INT32_MAX;

        for (int loop1 = n; loop1 > 1; --loop1) {
            int s = 0, t = 0;
            fill_n(f + 1, n, 0);
            seen.reset();

            int loop2 = loop1; while (loop2--) {
                int x = -1, fx = -1;
                for (int y = 1; y <= n; ++y) if (live[y] && !seen[y]) {
                    if (fx < f[y]) x = y, fx = f[y];
                }
                s = t; t = x;
                seen.set(x);
                for (int y = 1; y <= n; ++y) if (live[y] && !seen[y]) {
                    f[y] += wei[x][y];
                }
            }

            ans = min(ans, f[t]);
            live.reset(t);
            for (int x = 1; x <= n; ++x) if (live[x]) {
                wei[x][s] += wei[x][t];
                wei[s][x] = wei[x][s];
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
