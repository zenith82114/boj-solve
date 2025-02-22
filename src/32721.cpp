/*
 * Q32721 - graph theory; functional graph
 * Date: 2025.2.22
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 1'000'000> f, indeg;
bitset<1'000'000> vis;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    indeg.fill(0);
    for (int x = 0; x < n; ++x) {
        cin >> f[x], --f[x];
        ++indeg[f[x]];
    }

    int cnt = 0, x = 0;
    for (; !vis[x]; vis.set(x), x = f[x]) ++cnt;
    if (cnt == n && x == 0) { cout << 0; return 0; }
    else vis.reset();

    int ans = 0;
    for (int x = 0; x < n; ++x) if (indeg[x] == 0) {
        for (int y = x; !vis[y]; vis.set(y), y = f[y]) ++ans;
        --ans;
    }
    for (int x = 0; x < n; ++x) if (indeg[x] == 1 && !vis[x]) {
        for (int y = x; !vis[y]; vis.set(y), y = f[y]) ++ans;
        --ans;
    }
    cout << (n - ans);
    return 0;
}
