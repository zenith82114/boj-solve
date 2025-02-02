/*
 * Q29772 - min cost flow, priority queue
 * Date: 2025.2.2
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

int cost[200000][3];
char flow_s[200000] {}, flow_mid[200000][3] {};
int flow_t[3] {};
priority_queue<ii, vector<ii>, greater<> > q1[3], q2[3][3];

void install(int i) {
    for (int x = 0; x < 3; ++x) {
        q1[x].emplace(cost[i][x], i);
        for (int y = 0; y < 3; ++y) if (x != y) {
            q2[x][y].emplace(cost[i][y] - cost[i][x], i);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, K; cin >> n >> K;
    i64 ans = 0;
    for (int x = 0; x < 3; ++x)
    for (int i = 0; i < n; ++i) { cin >> cost[i][x]; ans += cost[i][x]; }
    for (int i = 0; i < n; ++i) install(i);

    for (int F = 2 * n; F--;) {
        int px = -1, pi = -1;
        int py = -1, pj = -1;
        int pz = -1, pk = -1;
        i64 best = INT64_MAX;

        for (int x = 0; x < 3; ++x) {
            while (!q1[x].empty()) {
                int i = q1[x].top().second;
                if (flow_s[i] < 2 && !flow_mid[i][x]) break;
                q1[x].pop();
            }
            if (q1[x].empty()) continue;
            auto [c1, i] = q1[x].top();
            if (flow_t[x] < n - K && best > c1) {
                px = x, pi = i, py = -1;
                best = c1;
            }

            for (int y = 0; y < 3; ++y) if (x != y) {
                while (!q2[x][y].empty()) {
                    int i = q2[x][y].top().second;
                    if (flow_mid[i][x] && !flow_mid[i][y]) break;
                    q2[x][y].pop();
                }
                if (q2[x][y].empty()) continue;
                auto [c2, j] = q2[x][y].top();
                if (flow_t[y] < n - K && best > (i64)c1 + c2) {
                    px = x, pi = i, py = y, pj = j, pz = -1;
                    best = (i64)c1 + c2;
                }

                int z = 3 ^ x ^ y;
                while (!q2[y][z].empty()) {
                    int i = q2[y][z].top().second;
                    if (flow_mid[i][y] && !flow_mid[i][z]) break;
                    q2[y][z].pop();
                }
                if (q2[y][z].empty()) continue;
                auto [c3, k] = q2[y][z].top();
                if (flow_t[z] < n - K && best > (i64)c1 + c2 + c3) {
                    px = x, pi = i, py = y, pj = j, pz = z, pk = k;
                    best = (i64)c1 + c2 + c3;
                }
            }
        }

        ++flow_s[pi];
        flow_mid[pi][px] = 1;
        install(pi);
        if (py == -1) {
            ++flow_t[px];
        }
        else if (pz == -1) {
            flow_mid[pj][px] = 0;
            flow_mid[pj][py] = 1;
            ++flow_t[py];
            install(pj);
        }
        else {
            flow_mid[pj][px] = 0;
            flow_mid[pj][py] = 1;
            flow_mid[pk][py] = 0;
            flow_mid[pk][pz] = 1;
            install(pj); install(pk);
        }
        ans -= best;
    }

    cout << ans;
    return 0;
}
