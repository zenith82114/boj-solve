/*
 * Q24437 - greedy
 * Date: 2026.1.13
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

const int MAXN = 5e4 + 5;
const int MAXM = 5e5 + 5;

int cnt[MAXN];
int max_cnt;
vector<int> buckets[MAXM];
int pos[MAXN];
int prv[MAXN], nxt[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        int m = 0;
        nxt[0] = 1;
        prv[n + 1] = n;
        nxt[n + 1] = n + 1;

        for (int c = 0; c <= max_cnt; ++c) buckets[c].clear();
        max_cnt = 0;

        for (int x = 1; x <= n; ++x) {
            cin >> cnt[x];
            m += cnt[x];
            max_cnt = max(max_cnt, cnt[x]);
            buckets[cnt[x]].push_back(x);
            pos[x] = buckets[cnt[x]].size() - 1;
            prv[x] = x - 1;
            nxt[x] = x + 1;
        }

        int last = 0;
        i64 ans = 0;
        bool fail = false;

        for (int t = 1; t <= m; ++t) {
            int rem = m - t + 1;
            int limit = (rem + 1) / 2;
            if (max_cnt > limit) { fail = true; break; }

            int x = -1;
            if (max_cnt == limit && (rem & 1)) {
                x = buckets[max_cnt].back();
                if (x == last) { fail = true; break; }
            } else {
                x = (nxt[0] != last ? nxt[0] : nxt[nxt[0]]);
                if (x > n) { fail = true; break; }
            }

            int y = buckets[cnt[x]].back();
            buckets[cnt[x]][pos[x]] = y;
            pos[y] = pos[x];
            buckets[cnt[x]].pop_back();

            if (cnt[x] == max_cnt && buckets[cnt[x]].empty()) --max_cnt;
            if (--cnt[x]) {
                buckets[cnt[x]].push_back(x);
                pos[x] = buckets[cnt[x]].size() - 1;
            } else {
                nxt[prv[x]] = nxt[x];
                prv[nxt[x]] = prv[x];
            }

            last = x;
            ans = (ans + 1ll*t*x) % 987654323;
        }

        if (fail) cout << "IMPOSSIBLE\n"; else cout << ans << '\n';
    }

    return 0;
}
