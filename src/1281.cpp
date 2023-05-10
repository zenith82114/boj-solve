/*
 * Q1281 - LP duality + Hungarian
 * Date: 2023.5.10
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    array<array<int, 256>, 256> w;
    for (auto& wr : w) wr.fill(0);

    array<int, 256> lx, ly, mx, my;
    lx.fill(0), ly.fill(0);
    mx.fill(-1), my.fill(-1);

    int N, M; cin >> N >> M;
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        cin >> w[i][j];
        lx[i] = max(lx[i], w[i][j]);
    }
    N = max(N, M);

    int K = 0;
    while (K < N) {
        int x = 0; for (; mx[x] != -1; ++x);
        bitset<256> S, T; S.set(x);
        array<int, 256> slk, slkx;
        for (int j = 0; j < N; ++j) {
            slk[j] = lx[x] + ly[j] - w[x][j];
            slkx[j] = x;
        }
        array<int, 256> ty; ty.fill(-1);

        while (1) {
            int y = 0;
            for (; y < N; ++y) if (!slk[y] && !T[y]) break;
            if (y == N) {
                int delta = INT_MAX;
                for (int j = 0; j < N; ++j) if (!T[j])
                    delta = min(delta, slk[j]);
                for (int n = 0; n < N; ++n) {
                    if (S[n]) lx[n] -= delta;
                    if (T[n]) ly[n] += delta;
                }
                for (int j = 0; j < N; ++j) if (!T[j]) {
                    slk[j] -= delta;
                    if (!slk[j]) y = j;
                }
            }
            ty[y] = slkx[y];

            if (my[y] == -1) {
                while (y != -1) {
                    my[y] = x = ty[y];
                    int yy = mx[x];
                    mx[x] = y; y = yy;
                }
                ++K; break;
            } else {
                int z = my[y];
                S.set(z), T.set(y);
                for (int j = 0; j < N; ++j) {
                    int s = lx[z] + ly[j] - w[z][j];
                    if (s < slk[j]) { slk[j] = s, slkx[j] = z; }
                }
            }
        }
    }

    int ans = 0;
    for (int n = 0; n < N; ++n) ans += lx[n] + ly[n];
    cout << ans;
    return 0;
}
