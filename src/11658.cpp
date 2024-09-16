/*
 * Q11658 - 2D segment tree
 * Date: 2024.9.16
 */

#include<bits/stdc++.h>
using namespace std;

int segt[2048][2048] {};
int tn;

void upd(int x, int y, int c) {
    segt[x |= tn][y |= tn] = c;
    for (int k = y >> 1; k; k >>= 1) {
        segt[x][k] = segt[x][k<<1] + segt[x][k<<1|1];
    }
    for (x >>= 1; x; x >>= 1) {
        segt[x][y] = segt[x<<1][y] + segt[x<<1|1][y];
        for (int k = y >> 1; k; k >>= 1) {
            segt[x][k] = segt[x][k<<1] + segt[x][k<<1|1];
        }
    }
}

int qry(
    int qu, int qd, int ql, int qr,
    int nu = 0, int nd = tn - 1, int nl = 0, int nr = tn - 1,
    int nx = 1, int ny = 1
) {
    if (qd < nu || nd < qu) return 0;
    if (qu <= nu && nd <= qd) {
        if (qr < nl || nr < ql) return 0;
        if (ql <= nl && nr <= qr) return segt[nx][ny];
        int mid = (nl + nr)>>1;
        return qry(qu, qd, ql, qr, nu, nd, nl, mid, nx, ny<<1)
            + qry(qu, qd, ql, qr, nu, nd, mid+1, nr, nx, ny<<1|1);
    }
    int mid = (nu + nd)>>1;
    return qry(qu, qd, ql, qr, nu, mid, nl, nr, nx<<1, ny)
        + qry(qu, qd, ql, qr, mid+1, nd, nl, nr, nx<<1|1, ny);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    tn = 1; while (tn < n) tn <<= 1;
    for (int x = 0; x < n; ++x)
    for (int y = 0; y < n; ++y) cin >> segt[tn|x][tn|y];

    for (int x = tn; x < tn + n; ++x)
    for (int y = tn - 1; y; --y) {
        segt[x][y] = segt[x][y<<1] + segt[x][y<<1|1];
    }
    for (int y = 0; y < tn + n; ++y)
    for (int x = tn - 1; x; --x) {
        segt[x][y] = segt[x<<1][y] + segt[x<<1|1][y];
    }

    while (m--) {
        int op; cin >> op;
        if (!op) {
            int x, y, c; cin >> x >> y >> c;
            upd(--x, --y, c);
        }
        else {
            int u, d, l, r; cin >> u >> l >> d >> r;
            cout << qry(--u, --d, --l, --r) << '\n';
        }
    }

    return 0;
}
