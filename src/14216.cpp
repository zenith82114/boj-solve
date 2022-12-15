/*
 * Q14216 - Hungarian alg.
 * Date: 2022.2.24
 *
 * Commented lines are for maximum assignment.
 */

#include<bits/stdc++.h>
using namespace std;

array<array<int, 500>, 500> D;
array<int, 500> lx, ly, mx, my, ty, slk, slkx;
array<bool, 500> S, T;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    int M = 0;
    lx.fill(0), ly.fill(0);
    mx.fill(-1), my.fill(-1);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> D[i][j];
            // add: lx[i] = max(lx[i], D[i][j]);
        }
    }

    while (M < N) {
        ty.fill(-1);
        S.fill(false), T.fill(false);
        int x;
        for (int i = 0; i < N; ++i)
            if (mx[i] < 0) {
                x = i;
                break;
            }
        S[x] = true;
        for (int j = 0; j < N; ++j) {
            slk[j] = D[x][j] - lx[x] - ly[j];
            // replace: slk[j] = lx[x] + ly[j] - D[x][j];
            slkx[j] = x;
        }

        while (true) {
            int y = -1;
            for (int j = 0; j < N; ++j)
                if (!slk[j] && !T[j]) {
                    y = j;
                    break;
                }
            if (y < 0) {
                int delta = INT_MAX;
                for (int j = 0; j < N; ++j) if (!T[j])
                    delta = min(delta, slk[j]);
                for (int i = 0; i < N; ++i) {
                    if (S[i]) lx[i] += delta;
                    // replace: if (S[i]) lx[i] -= delta;
                    if (T[i]) ly[i] -= delta;
                    // replace: if (T[i]) ly[i] += delta;
                }
                for (int j = 0; j < N; ++j) if (!T[j]) {
                    slk[j] -= delta;
                    if (!slk[j])
                        y = j;
                }
            }
            ty[y] = slkx[y];

            if (my[y] < 0) {
                while (~y) {
                    x = ty[y];
                    my[y] = x;
                    int yy = mx[x];
                    mx[x] = y;
                    y = yy;
                }
                M++;
                break;
            }
            else {
                int z = my[y];
                S[z] = true, T[y] = true;
                for (int y = 0; y < N; ++y) {
                    int s = D[z][y] - lx[z] - ly[y];
                    // replace: int s = lx[z] + ly[y] - D[z][y];
                    if (s < slk[y]) {
                        slk[y] = s;
                        slkx[y] = z;
                    }
                }
            }
        }
    }

    int C = 0;
    for (int i = 0; i < N; ++i)
        C += lx[i] + ly[i];
    cout << C << '\n';
    return 0;
}
