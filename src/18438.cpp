/*
 * Q18438 - Hirschberg's
 * Date: 2026.2.26
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 1e4 + 4;

string s, t, u;
int fw[2][MAXN], bw[2][MAXN];

void dnc(int sl, int sr, int tl, int tr) {
    if (sl == sr || tl == tr) return;
    if (sl + 1 == sr) {
        for (int j = tl; j < tr; ++j) {
            if (s[sl] == t[j]) { u.push_back(s[sl]); return; }
        }
        return;
    }

    int h = (sl + sr)/2;

    fill(fw[~sl&1] + tl, fw[~sl&1] + tr, 0);
    for (int i = sl; i < h; ++i) {
        int now = i&1, pre = ~i&1;
        fw[now][tl] = fw[pre][tl] | (s[i] == t[tl]);
        for (int j = tl + 1; j < tr; ++j) {
            fw[now][j] = (s[i] == t[j] ? fw[pre][j - 1] + 1 : max(fw[now][j - 1], fw[pre][j]));
        }
    }

    fill(bw[sr&1] + tl, bw[sr&1] + tr, 0);
    for (int i = sr - 1; i >= h; --i) {
        int now = i&1, pre = ~i&1;
        bw[now][tr - 1] = bw[pre][tr - 1] | (s[i] == t[tr - 1]);
        for (int j = tr - 2; j >= tl; --j) {
            bw[now][j] = (s[i] == t[j] ? bw[pre][j + 1] + 1 : max(bw[now][j + 1], bw[pre][j]));
        }
    }

    const auto& fw_done = fw[~h&1];
    const auto& bw_done = bw[h&1];

    int best = bw_done[tl], best_j = tl;
    for (int j = tl + 1; j < tr; ++j) {
        if (best < fw_done[j - 1] + bw_done[j]) {
            best = fw_done[j - 1] + bw_done[j], best_j = j;
        }
    }
    if (best < fw_done[tr - 1]) best = fw_done[tr - 1], best_j = tr;
    dnc(sl, h, tl, best_j);
    dnc(h, sr, best_j, tr);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s >> t;
    dnc(0, s.size(), 0, t.size());
    cout << u.size() << '\n' << u;
    return 0;
}
