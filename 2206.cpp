/*
 * Q2206 - Grid maze BFS
 * Date: 2021.7.15
 */

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
constexpr int INF = INT32_MAX;

int N, M;
bool A[1001][1001];
int B[1001][1001], C[1001][1001];
int dm[4] = { 1,0,-1,0 };
int dn[4] = { 0,-1,0,1 };

inline bool IN_RANGE(int n, int m) {
    return (n > 0 && n <= N && m > 0 && m <= M);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> M;
    for (int n = 1; n <= N; ++n) {
        for (int m = 1; m <= M; ++m) {
            char t; cin >> t;
            // data (map)
            A[n][m] = t - '0';
            // "footprint" array
            // -1: not reached
            // 0: reached using wallbreak
            // 1: reached without using wallbreak
            B[n][m] = -1;
            // cost array - least steps known so far needed to reach [n][m]
            C[n][m] = INF;
        }
    }

    queue<tuple<int, int, int, int> > Q;
    Q.emplace(1, 1, 1, 1);
    while (!Q.empty()) {
        auto [n, m, b, c] = Q.front(); Q.pop();
        // When we should update a cell:
        // 1. we find a "better" state for it (B value increases)
        // 2. we find a "shorter" path to it (C value decreases with same B value)
        if (B[n][m] < b || (B[n][m] == b && C[n][m] > c)) {
            B[n][m] = b;
            C[n][m] = c;
            if (n == N && m == M)
                break;
            for (int k = 0; k < 4; ++k) {
                int n_ = n + dn[k];
                int m_ = m + dm[k];
                if (IN_RANGE(n_, m_) &&
                    (B[n_][m_] < b ||
                    (B[n_][m_] == b && C[n_][m_] > c + 1))) {
                    if (!A[n_][m_])
                        Q.emplace(n_, m_, b, c + 1);
                    // use wallbreak if not used yet
                    else if (b)
                        Q.emplace(n_, m_, 0, c + 1);
                }
            }
        }
    }
    if (C[N][M] == INF) cout << -1;
    else cout << C[N][M];
    cout << '\n';

    return 0;
}
