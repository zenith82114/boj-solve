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
    int t;
    visited[n] = true;
    for (int& m : G[n]) {
        t = taken[m];
        if (t == 0 || (!visited[t] && match(t))) {
            taken[m] = n;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, n, m, k, C;

    cin >> N >> M;
    for (n = 1; n <= N; n++) {
        cin >> k;
        while (k--) {
            cin >> m;
            G[n].push_back(m);
        }
    }

    taken.fill(0);
    C = 0;
    for (n = 1; n <= N; n++) {
        visited.fill(false);
        if (match(n)) C++;
    }

    cout << C << '\n';
    return 0;
}
