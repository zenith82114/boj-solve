/*
 * Q11014 - Gallai's theorem and Konig's theorem
 * Date: 2022.1.25
 */

#include<iostream>
#include<array>
#include<vector>
using namespace std;

array<vector<int>, 6400> G;
array<int, 6400> taken;
array<bool, 6400> B, visited;

bool match(int x) {
    int w;
    visited[x] = true;
    for (int& y : G[x]) {
        w = taken[y];
        if (w == -1 || (!visited[w] && match(w))) {
            taken[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    while (TC--) {
        int N, M; cin >> N >> M;
        int S = 0;
        for (int v = 0; v < N*M; ++v) {
            char c; cin >> c;
            if (c == '.') {
                B[v] = true;
                S++;
            }
            else B[v] = false;
        }

        vector<int> X;
        for (int n = 0; n < N; ++n) {
            for (int m = 1; m < M; m += 2) {
                int v = n*M + m;
                if (B[v]) {
                    G[v].clear();
                    if (m > 0) {
                        if (n > 0 && B[v-M-1])
                            G[v].push_back(v-M-1);
                        if (B[v-1])
                            G[v].push_back(v-1);
                        if (n < N-1 && B[v+M-1])
                            G[v].push_back(v+M-1);
                    }
                    if (m < M-1) {
                        if (n > 0 && B[v-M+1])
                            G[v].push_back(v-M+1);
                        if (B[v+1])
                            G[v].push_back(v+1);
                        if (n < N-1 && B[v+M+1])
                            G[v].push_back(v+M+1);
                    }
                    if (!G[v].empty())
                        X.push_back(v);
                }
            }
        }

        taken.fill(-1);
        for (int& x : X) {
            visited.fill(false);
            if (match(x)) S--;
        }
        cout << S << '\n';
    }

    return 0;
}
