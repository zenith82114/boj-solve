/*
 * Q1616 - Eulerian circuit
 * Date: 2023.8.7
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[5'000'000];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int K, M; cin >> K >> M;
    if (M == 1) {
        for (int x = 0; x < K; ++x) cout << x << ' ';
        return 0;
    }

    int E = 1; for (int i = 0; i < M; ++i) E *= K; // K**M
    int W = E/K/K; // K**(M-2)

    for (int a = 0; a < K; ++a)
    for (int b = 0; b < W; ++b)
    for (int c = 0; c < K; ++c) {
        int x = a*W + b;
        int y = b*K + c;
        adj[x].emplace_back(y);
    }

    stack<int> stk; stk.emplace(0);
    vector<int> path; path.reserve(E+1);
    while (!stk.empty()) {
        int x = stk.top();
        if (!adj[x].empty()) {
            int y = adj[x].back(); adj[x].pop_back();
            stk.emplace(y);
        } else {
            path.emplace_back(x%K);
            stk.pop();
        }
    }
    path.pop_back();
    for (int x : path) cout << x << ' ';
    return 0;
}
