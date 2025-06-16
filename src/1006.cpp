/*
 * Q1006 - greedy, maximum matching
 * Date: 2025.6.16
 *
 * References
 * - https://blog.bubbler.blue/posts/boj-problems/1006_greedy/
 * - https://www.acmicpc.net/source/83177128
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

int n, w;
int a[2][10000];
vector<ii> g[2][10000];
int e[2];
char used[2][10000];
int deg[2][10000];

int solve() {
    int ans = 0;
    queue<ii> q;

    for (int i : {0, 1}) {
        memset(used[i], 0, n);
        if (e[i] && n > 1) {
            used[i][0] = used[i][n - 1] = 1;
            if (a[i][0] + a[i][n - 1] <= w) ++ans;
        }
        for (int j = 0; j < n; ++j) {
            deg[i][j] = g[i][j].size();
            if (!used[i][j] && deg[i][j] == 1) q.emplace(i, j);
        }
    }

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        if (used[i][j]) continue;
        for (auto [ni, nj] : g[i][j]) if (!used[ni][nj]) {
            ++ans;
            used[i][j] = used[ni][nj] = 1;
            for (auto [nni, nnj] : g[ni][nj]) if (!used[nni][nnj]) {
                if (--deg[nni][nnj] == 1) q.emplace(nni, nnj);
            }
            break;
        }
    }

    for (int j = 0; j < n; ++j) {
        if (!used[0][j] && !used[1][j] && a[0][j] + a[1][j] <= w) {
            ++ans;
            used[0][j] = used[1][j] = 1;
        }
        else if (j + 1 < n) for (int i : {0, 1}) {
            if (!used[i][j] && !used[i][j + 1] && a[i][j] + a[i][j + 1] <= w) {
                ++ans;
                used[i][j] = used[i][j + 1] = 1;
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    const int d[] = {0, 1, 0, -1, 0};

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> w;
        for (int i : {0, 1}) for (int j = 0; j < n; ++j) cin >> a[i][j];
        for (int i : {0, 1}) for (int j = 0; j < n; ++j) {
            g[i][j].clear();
            for (int k = 0; k < 4; ++k) {
                int ni = i + d[k], nj = j + d[k + 1];
                if (ni < 0 || ni >= 2 || nj < 0 || nj >= n) continue;
                if (a[i][j] + a[ni][nj] <= w) g[i][j].emplace_back(ni, nj);
            }
        }

        int ans = 0;
        for (int m : {0, 1, 2, 3}) {
            e[0] = m & 1, e[1] = m & 2;
            ans = max(ans, solve());
        }
        cout << (2*n - ans) << '\n';
    }

    return 0;
}
