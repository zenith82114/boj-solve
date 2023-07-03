/*
 * Q16129 - Backtracking
 * Date: 2023.7.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int R, C;

constexpr int dr[4] { 1, -1, 0, 0 };
constexpr int dc[4] { 0, 0, 1, -1 };
constexpr int va[5] { 0, 1, 1, 0, 1 };

vector<pair<int, int> > buf;
int step = 0;

i64 backtrack(int r, int c) {
    if (step == 4) {
        return 1;
    }
    i64 ans = 0;
    buf.emplace_back(r, c); ++step;
    for (int k = 0; k < 4; ++k) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if (va[(nr * C + nc) % 5] != va[step]) continue;
        if (any_of(buf.begin(), buf.end(), [nr, nc] (const pair<int, int>& p) {
            return p == make_pair(nr, nc);
        })) continue;
        ans += backtrack(nr, nc);
    }
    buf.pop_back(); --step;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> R >> C;

    vector<int> rv, cv;
    if (R < 13) for (int r = 0; r < R; ++r) rv.emplace_back(r);
    else rv = { 0, 1, 2, 3, 4, 5, 6, 7, 8, R-4, R-3, R-2, R-1 };
    if (C < 13) for (int c = 0; c < C; ++c) cv.emplace_back(c);
    else cv = { 0, 1, 2, 3, 4, 5, 6, 7, 8, C-4, C-3, C-2, C-1 };

    i64 ans = 0;
    for (int r : rv) for (int c : cv) {
        if (va[(r * C + c) % 5] != 0) continue;
        i64 tmp = backtrack(r, c);
        if (R > 13 && 3 < r && r < 9) tmp *= (R - r) / 5;
        if (C > 13 && 3 < c && c < 9) tmp *= (C - c) / 5;
        ans += tmp;
    }
    cout << ans;
    return 0;
}
