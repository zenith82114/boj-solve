/*
 * Q16220 - greedy
 * Date: 2025.7.31
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

array<int, 500'000> l, r;
bitset<500'000> vis;
priority_queue<pair<int, int> > pq;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 0; x < n; ++x) cin >> l[x] >> r[x];
    vector<int> sl(n), sr(n);
    iota(sl.begin(), sl.end(), 0);
    sort(sl.begin(), sl.end(), [](int x, int y){ return l[x] > l[y]; });
    iota(sr.begin(), sr.end(), 0);
    sort(sr.begin(), sr.end(), [](int x, int y){ return r[x] > r[y]; });

    int j = 0, ans = 0;
    for (int i = 0; i < n; ++i) if (!vis[sl[i]]) {
        int x = sl[i];
        vis.set(x);

        while (j < n && l[x] <= r[sr[j]]) {
            int y = sr[j];
            if (!vis[y]) pq.emplace(l[y], y);
            ++j;
        }
        while (!pq.empty() && vis[pq.top().second]) pq.pop();
        if (!pq.empty()) {
            int y = pq.top().second; pq.pop();
            vis.set(y);
            ++ans;
        }
    }

    cout << ans;
    return 0;
}
