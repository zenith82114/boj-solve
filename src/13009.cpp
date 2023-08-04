/*
 * Q13009 - Floyd-Warshall + DnC
 * Date: 2023.8.4
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
constexpr i64 inf = INT64_MAX>>1;

i64 dis[51][51] {};
i64 tmp[51][51];
i64 sqr[51][51];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M, C; cin >> N >> M >> C;
    vector<tuple<int, int, int> > edges;
    for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j) dis[i][j] = inf;
    while (M--) {
        int i, j, w; cin >> i >> j >> w;
        dis[i][j] = min(dis[i][j], (i64)w);
        edges.emplace_back(i, j, w);
    }
    for (int i = 1; i <= N; ++i) dis[i][i] = 0;

    for (int k = 1; k <= N; ++k)
    for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    memcpy(sqr, dis, sizeof dis);
    for (const auto& [x, y, w] : edges) {
        for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            sqr[i][j] = min(sqr[i][j], dis[i][x] - w + dis[y][j]);
    }

    for (; C; C >>= 1) {
        if (C&1) {
            for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j) tmp[i][j] = inf;

            for (int k = 1; k <= N; ++k)
            for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                tmp[i][j] = min(tmp[i][j], dis[i][k] + sqr[k][j]);
            memcpy(dis, tmp, sizeof tmp);
        }
        for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j) tmp[i][j] = inf;

        for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            tmp[i][j] = min(tmp[i][j], sqr[i][k] + sqr[k][j]);
        memcpy(sqr, tmp, sizeof tmp);
    }

    cout << dis[1][N];
    return 0;
}
