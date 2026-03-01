/*
 * Q18438 - Hirschberg's
 * Date: 2026.3.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e4 + 4;

string u;
int fw[2][MAXN], bw[2][MAXN];

void dnc(const string_view s, const string_view t) {
    if (s.empty() || t.empty()) return;
    if (s.size() == 1u) {
        if (t.find(s[0]) != string_view::npos) u.push_back(s[0]);
        return;
    }

    int n = s.size(), m = t.size();

    fill_n(fw[1], m + 1, 0);
    for (int i = 0; i < n/2; ++i) {
        int now = i&1, pre = ~i&1;
        fw[now][0] = 0;
        for (int j = 1; j <= m; ++j) {
            fw[now][j] = (s[i] == t[j - 1]
                ? fw[pre][j - 1] + 1 : max(fw[now][j - 1], fw[pre][j]));
        }
    }

    fill_n(bw[n&1], m + 1, 0);
    for (int i = n - 1; i >= n/2; --i) {
        int now = i&1, pre = ~i&1;
        bw[now][m] = 0;
        for (int j = m - 1; j >= 0; --j) {
            bw[now][j] = (s[i] == t[j]
                ? bw[pre][j + 1] + 1 : max(bw[now][j + 1], bw[pre][j]));
        }
    }

    const auto& fw_last = fw[~(n/2)&1];
    const auto& bw_last = bw[(n/2)&1];

    int best = bw_last[0], best_j = 0;
    for (int j = 1; j <= m; ++j) {
        if (best < fw_last[j] + bw_last[j]) {
            best = fw_last[j] + bw_last[j], best_j = j;
        }
    }
    dnc(s.substr(0, n/2), t.substr(0, best_j));
    dnc(s.substr(n/2), t.substr(best_j));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t; cin >> s >> t;
    dnc(s, t);
    cout << u.size() << '\n' << u;
    return 0;
}
