/*
 * Q1725b - disjoint sets
 * Date: 2025.6.6
 */

#include<bits/stdc++.h>
using namespace std;

int h[100000], dsu[100000];

int find(int x) {
    if (dsu[x] < 0) return x;
    return dsu[x] = find(dsu[x]);
}

int unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (dsu[x] > dsu[y]) swap(x, y);
        dsu[x] += dsu[y];
        dsu[y] = x;
    }
    return -dsu[x];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> h[i];
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [](int i, int j) { return h[i] > h[j]; });
    memset(dsu, -1, sizeof dsu);

    int ans = 0;
    for (int i : v) {
        ans = max(ans, h[i]);
        if (i > 0 && h[i - 1] >= h[i]) ans = max(ans, h[i] * unite(i - 1, i));
        if (i + 1 < n && h[i] <= h[i + 1]) ans = max(ans, h[i] * unite(i, i + 1));
    }
    cout << ans;
    return 0;
}
