/*
 * Q1315 - BFS + prefix sum
 * Date: 2023.11.14
 */

#include<bits/stdc++.h>
using namespace std;

int csum[1001][1001] {};
int psum[1001][1001] {};
bool vis[1001][1001] {};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    while (n--) {
        int x, y, z; cin >> x >> y >> z;
        csum[x][y]++;
        psum[x][y] += z;
    }

    for (int x = 1; x <= 1000; ++x)
    for (int y = 1; y <= 1000; ++y) {
        csum[x][y] += csum[x-1][y] + csum[x][y-1] - csum[x-1][y-1];
        psum[x][y] += psum[x-1][y] + psum[x][y-1] - psum[x-1][y-1];
    }

    queue<pair<int, int> > q; q.emplace(1, 1);
    vis[1][1] = true;
    int ans = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        int cnt = csum[x][1000] + csum[1000][y] - csum[x][y];
        int pnt = psum[x][1000] + psum[1000][y] - psum[x][y] - x - y + 2;
        ans = max(ans, cnt);
        if (!pnt) continue;
        if (x < 1000 && !vis[x+1][y]) {
            vis[x+1][y] = true;
            q.emplace(x+1, y);
        }
        if (y < 1000 && !vis[x][y+1]) {
            vis[x][y+1] = true;
            q.emplace(x, y+1);
        }
    }
    cout << ans;
    return 0;
}
