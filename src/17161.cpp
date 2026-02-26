/*
 * Q17161 - Hirschberg's
 * Date: 2026.2.27
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 17004;

string s, t;
int fw[2][MAXN], bw[2][MAXN];

void dnc(int sl, int sr, int tl, int tr) {
    if (sl == sr) {
        for (int j = tl; j < tr; ++j) cout << "a " << t[j] << '\n';
        return;
    }
    if (tl == tr) {
        for (int i = sl; i < sr; ++i) cout << "d " << s[i] << '\n';
        return;
    };
    if (sl + 1 == sr) {
        int f = -1;
        for (int j = tl; j < tr; ++j) {
            if (s[sl] == t[j]) { f = j; break; }
        }
        if (f != -1) {
            for (int j = tl; j < f; ++j) cout << "a " << t[j] << '\n';
            cout << "c " << s[sl] << '\n';
            for (int j = f + 1; j < tr; ++j) cout << "a " << t[j] << '\n';
        } else {
            cout << "m " << t[tl] << '\n';
            for (int j = tl + 1; j < tr; ++j) cout << "a " << t[j] << '\n';
        }
        return;
    }

    int h = (sl + sr)/2;

    for (int j = tl; j <= tr; ++j) fw[~sl&1][j] = j - tl;
    for (int i = sl; i < h; ++i) {
        int now = i&1, pre = ~i&1;
        fw[now][tl] = fw[pre][tl] + 1;
        for (int j = tl + 1; j <= tr; ++j) {
            fw[now][j] = min({
                fw[pre][j] + 1, fw[now][j - 1] + 1, fw[pre][j - 1] + (s[i] != t[j - 1])});
        }
    }

    for (int j = tl; j <= tr; ++j) bw[sr&1][j] = tr - j;
    for (int i = sr - 1; i >= h; --i) {
        int now = i&1, pre = ~i&1;
        bw[now][tr] = bw[pre][tr] + 1;
        for (int j = tr - 1; j >= tl; --j) {
            bw[now][j] = min({
                bw[pre][j] + 1, bw[now][j + 1] + 1, bw[pre][j + 1] + (s[i] != t[j])});
        }
    }

    const auto& fw_done = fw[~h&1];
    const auto& bw_done = bw[h&1];

    int best = 1e9, best_j = tl;
    for (int j = tl; j <= tr; ++j) {
        if (best > fw_done[j] + bw_done[j]) {
            best = fw_done[j] + bw_done[j], best_j = j;
        }
    }
    dnc(sl, h, tl, best_j);
    dnc(h, sr, best_j, tr);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s >> t;
    dnc(0, s.size(), 0, t.size());
    return 0;
}
