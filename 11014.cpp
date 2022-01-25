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
    cin.tie(0)->sync_with_stdio(0);
    vector<int> X;
    int TC, N, M, v, S;
    char c;

    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        S = 0;
        for (v = 0; v < N*M; v++) {
            cin >> c;
            if (c == '.') {
                B[v] = true;
                S++;
            }
            else B[v] = false;
        }

        X.clear();
        for (int n = 0; n < N; n++) {
            for (int m = 1; m < M; m += 2) {
                v = n*M + m;
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
