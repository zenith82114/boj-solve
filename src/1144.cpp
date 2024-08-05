/*
 * Q1144 - Connection Profile DP
 * Date: 2024.8.5
 */

#include<bits/stdc++.h>
using namespace std;

int n, m;
int arr[9][9];
map<int, int> mem[9][9];

inline int get_(int mask, int i) {
    return (mask >> (3*(m - 1 - i))) & 7;
}

inline void set_(int& mask, int i, int c) {
    mask &= ~(7 << (3*(m - 1 - i)));
    mask |= (c << (3*(m - 1 - i)));
}

// passing (excluding) current cell does not form a dangling CC
bool try_pass(int mask) {
    if (get_(mask, 0) == 0) return true;
    for (int i = 1; i < m; ++i) {
        if (get_(mask, i) == 1) return true;
    }
    return false;
}

// zero or one CC so far
bool valid(int mask) {
    for (int i = 0; i < m; ++i) {
        if (get_(mask, i) > 1) return false;
    }
    return true;
}

int next_mask(int mask, bool pass, bool first_col = false) {
    const static int FULL_MASK = (1 << 3*m) - 1;
    int n_mask = (mask << 3) & FULL_MASK;
    if (!pass) {
        int a = get_(mask, 0);
        int b = first_col? 0 : get_(mask, m - 1);
        n_mask = (mask << 3) & FULL_MASK;
        if (!a && !b) n_mask |= 7;
        else if (!a) n_mask |= b;
        else if (!b) n_mask |= a;
        else {
            for (int i = 0; i < m; ++i) {
                if (get_(n_mask, i) == b) set_(n_mask, i, a);
            }
            n_mask |= a;
        }
    }

    // normalize
    int lut[8] {};
    int ptr = 0;
    mask = n_mask; n_mask = 0;
    for (int i = 0; i < m; ++i) {
        n_mask <<= 3;
        int k = get_(mask, i);
        if (k == 0) continue;
        if (!lut[k]) lut[k] = ++ptr;
        n_mask |= lut[k];
    }
    return n_mask;
}

int dp(int x, int y, int mask) {
    if (x == n) return valid(mask)? 0 : 0xdead;
    if (mem[x][y].count(mask)) return mem[x][y][mask];

    int& ret = mem[x][y][mask] = 0xdead;
    int nx = x, ny = y + 1;
    if (ny == m) ++nx, ny = 0;

    if (try_pass(mask)) {
        ret = min(ret, dp(nx, ny, next_mask(mask, true)));
    }
    ret = min(ret, arr[x][y] + dp(nx, ny, next_mask(mask, false, !y)));
    if (valid(mask)) ret = min(ret, 0);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) cin >> arr[i][j];
    cout << dp(0, 0, 0);

    return 0;
}
