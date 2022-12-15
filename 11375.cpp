/*
 * Q11375 - Bipartite matching by recursion
 * Date: 2022.1.23
 */

#include<iostream>
#include<array>
#include<vector>
using namespace std;

array<vector<int>, 1001> G;
array<int, 1001> taken;
array<bool, 1001> visited;

bool match(int n) {
    visited[n] = true;
    for (int& m : G[n]) {
        int& t = taken[m];
        if (t == 0 || (!visited[t] && match(t))) {
            t = n;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;
    for (int n = 1; n <= N; ++n) {
        int k; cin >> k;
        while (k--) {
            int m; cin >> m;
            G[n].push_back(m);
        }
    }

    taken.fill(0);
    int C = 0;
    for (int n = 1; n <= N; ++n) {
        visited.fill(false);
        if (match(n)) C++;
    }

    cout << C << '\n';
    return 0;
}
