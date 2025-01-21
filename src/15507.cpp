/*
 * Q15507 - Z function, BFS
 * Date: 2025.1.21
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

array<int, 1'000'000> z;
int dist[20][500'001] {};
vector<ii> dirty;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    string s; cin >> s;
    z[0] = n;
    for (int l = 0, r = 0, i = 1; i < n; ++i) {
        if (i < r) z[i] = min(z[i - l], r - i);
        else z[i] = 0;
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }

    dist[0][0] = 0;
    int ans = INT32_MAX;

    for (int c = 0; (1 << c) + 1 <= n; ++c) {
        if (n % ((1 << c) + 1)) continue;
        int m = n / ((1 << c) + 1);

        for (const auto& [k, i] : dirty) dist[k][i] = 0;
        dirty.clear();

        queue<ii> q; q.emplace(0, 0);
        while (!q.empty()) {
            auto [k, i] = q.front(); q.pop();
            if (i == m) {
                if (k == c) {
                    ans = min(ans, dist[k][i]);
                    break;
                }
                continue;
            }
            int j = (m << k) + i;
            if (s[i] == s[j] && !dist[k][i + 1]) {
                dist[k][i + 1] = dist[k][i] + 1;
                q.emplace(k, i + 1);
                dirty.emplace_back(k, i + 1);
            }
            if (z[i] >= i && z[j] >= j && !dist[k + 1][2 * i]) {
                dist[k + 1][2 * i] = dist[k][i] + 1;
                q.emplace(k + 1, 2 * i);
                dirty.emplace_back(k + 1, 2 * i);
            }
        }
    }

    cout << (ans < INT32_MAX? ans : -1);
    return 0;
}
