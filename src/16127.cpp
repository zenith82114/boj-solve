/*
 * Q16127 - directed MST
 * Date: 2025.5.17
 */

#include<bits/stdc++.h>
using namespace std;

int q[304];
int w[304][304];
int mw[304], mx[304], label[304];
struct edge {
    int x, y, w;
    edge(int x, int y, int w) : x(x), y(y), w(w) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> q[x];
    vector<edge> edges;
    for (int x = 0; x <= n; ++x) {
        w[x][0] = INT32_MAX;
        for (int y = 1; y <= n; ++y) {
            cin >> w[x][y];
            if (x != y) edges.emplace_back(x, y, w[x][y]);
        }
    }

    int k = n;
    int64_t ans = 0;
    bool done = false;
    while (!done) {
        fill_n(mw + 1, k, INT32_MAX);
        mw[0] = 0;
        for (const auto& [x, y, w] : edges) {
            if (mw[y] > w) { mw[y] = w; mx[y] = x; }
        }
        for (int x = 1; x <= k; ++x) ans += mw[x];

        fill_n(label + 1, k, -1);
        label[0] = 0;
        int nk = 0;
        for (int x = 1; x <= k; ++x) if (label[x] == -1) {
            int y;
            for (y = x; label[y] == -1; y = mx[y]) label[y] = -2;
            if (label[y] == -2) {
                ++nk;
                for (; label[y] == -2; y = mx[y]) label[y] = nk;
            }
            for (y = x; label[y] == -2; y = mx[y]) label[y] = ++nk;
        }

        if (nk == k) done = true;
        else {
            vector<edge> new_edges;
            for (const auto& [x, y, w] : edges) if (label[x] != label[y]) {
                new_edges.emplace_back(label[x], label[y], w - mw[y]);
            }
            edges.swap(new_edges);
            k = nk;
        }
    }

    for (int y = 1; y <= n; ++y) {
        mw[y] = INT32_MAX;
        for (int x = 0; x <= n; ++x) mw[y] = min(mw[y], w[x][y]);
        ans += 1ll * (q[y] - 1) * mw[y];
    }
    cout << ans;
    return 0;
}
