/*
 * Q18438 - Hirschburg's
 * Date: 2026.2.13
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

    fill(fw[1] + tl, fw[1] + tr, 0);
    for (int i = sl; i < h; ++i) {
        copy(fw[1] + tl, fw[1] + tr, fw[0] + tl);
        fw[1][tl] = fw[0][tl] | (s[i] == t[tl]);
        for (int j = tl + 1; j < tr; ++j) {
            fw[1][j] = (s[i] == t[j] ? fw[0][j - 1] + 1 : max(fw[1][j - 1], fw[0][j]));
        }
    }

    fill(bw[1] + tl, bw[1] + tr, 0);
    for (int i = sr - 1; i >= h; --i) {
        copy(bw[1] + tl, bw[1] + tr, bw[0] + tl);
        bw[1][tr - 1] = bw[0][tr - 1] | (s[i] == t[tr - 1]);
        for (int j = tr - 2; j >= tl; --j) {
            bw[1][j] = (s[i] == t[j] ? bw[0][j + 1] + 1 : max(bw[1][j + 1], bw[0][j]));
        }
    }

    int best = bw[1][tl], best_j = tl;
    for (int j = tl + 1; j < tr; ++j) {
        if (best < fw[1][j - 1] + bw[1][j]) {
            best = fw[1][j - 1] + bw[1][j], best_j = j;
        }
    }
    if (best < fw[1][tr - 1]) best = fw[1][tr - 1], best_j = tr;
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
