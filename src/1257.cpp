/*
 * Q1257 - 0-1 BFS
 * Date: 2024.5.30
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    i64 M; cin >> M;
    int N; cin >> N;
    vector<int> A(N);
    int P = 0;
    for (int& a : A) cin >> a, P = max(P, a);

    vector<int> dist(P, P); dist[0] = 0;
    deque<int> dq; dq.emplace_front(0);
    while (!dq.empty()) {
        int x = dq.front(); dq.pop_front();
        for (int a : A) {
            int y = x + a;
            if (y < P) {
                if (dist[y] > dist[x] + 1) {
                    dist[y] = dist[x] + 1;
                    dq.emplace_back(y);
                }
            }
            else if (dist[y - P] > dist[x]) {
                dist[y - P] = dist[x];
                dq.emplace_front(y - P);
            }
        }
    }
    cout << (M / P) + dist[M % P];
    return 0;
}
