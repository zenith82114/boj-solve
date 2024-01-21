/*
 * Q16933 - BFS, greedy
 * Date: 2024.1.21
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int dx[] = { 1, -1, 0, 0 };
constexpr int dy[] = { 0, 0, 1, -1 };
char b[1000][1000];
int use[1000][1000][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M, K; cin >> N >> M >> K;
    for (int x = 0; x < N; ++x)
    for (int y = 0; y < M; ++y) {
        cin >> b[x][y];
        use[x][y][0] = use[x][y][1] = K+1;
    }

    queue<tuple<int, int, int> > q;
    q.emplace(0, 0, 0);
    use[0][0][1] = 0;

    int ans = 1;
    while (!q.empty()) {
        int sz = q.size();
        int z = ans&1, nz = ~ans&1;
        while (sz--) {
            auto [x, y, u] = q.front(); q.pop();
            if (x == N-1 && y == M-1) {
                cout << ans; return 0;
            }
            if (use[x][y][nz] > u) {
                use[x][y][nz] = u;
                q.emplace(x, y, u);
            }
            for (int k = 0; k < 4; ++k) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx == -1 || nx == N || ny == -1 || ny == M) continue;
                if (b[nx][ny] == '0' && use[nx][ny][nz] > u) {
                    use[nx][ny][nz] = u;
                    q.emplace(nx, ny, u);
                }
                else if (b[nx][ny] == '1' && z == 1 && use[nx][ny][nz] > u+1) {
                    use[nx][ny][nz] = u+1;
                    q.emplace(nx, ny, u+1);
                }
            }
        }
        ++ans;
    }

    cout << -1; return 0;
}
