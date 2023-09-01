/*
 * Q2206 - BFS
 * Date: 2023.9.2
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int inf = INT32_MAX;
constexpr int dx[] = { 1, -1, 0, 0 };
constexpr int dy[] = { 0, 0, 1, -1 };
char b[1000][1000];
int dist[1000][1000][2] {};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    for (int x = 0; x < N; ++x)
    for (int y = 0; y < M; ++y) {
        cin >> b[x][y];
        dist[x][y][0] = dist[x][y][1] = inf;
    }

    queue<tuple<int, int, int> > q;
    q.emplace(0, 0, 0);
    dist[0][0][0] = 1;

    while (!q.empty()) {
        auto [x, y, k] = q.front(); q.pop();
        for (int t = 0; t < 4; ++t) {
            int nx = x + dx[t];
            int ny = y + dy[t];
            if (nx == -1 || nx == N || ny == -1 || ny == M) continue;
            if (b[nx][ny] == '0' && dist[nx][ny][k] > dist[x][y][k] + 1) {
                dist[nx][ny][k] = dist[x][y][k] + 1;
                q.emplace(nx, ny, k);
            }
            else if (b[nx][ny] == '1' && !k && dist[nx][ny][1] > dist[x][y][0] + 1) {
                dist[nx][ny][1] = dist[x][y][0] + 1;
                q.emplace(nx, ny, 1);
            }
        }
    }

    int ans = min(dist[N-1][M-1][0], dist[N-1][M-1][1]);
    cout << (ans == inf? -1 : ans);
    return 0;
}
