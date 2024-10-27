/*
 * Q1230 - DP
 * Date: 2024.10.27
 */

#include<bits/stdc++.h>
using namespace std;

int E[1004][1004];
int D[1004][1004];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    constexpr int inf = 0xc0ffee;

    string A, B;
    getline(cin, A); A.insert(A.begin(), '#');
    getline(cin, B); B.insert(B.begin(), '#');
    int n = A.size(), m = B.size();

    for (int j = 0; j < m; ++j) {
        E[0][j] = 1;
        D[0][j] = inf;
    }
    E[0][0] = 0;
    for (int i = 1; i < n; ++i) {
        E[i][0] = D[i][0] = inf;
        for (int j = 1; j < m; ++j) {
            E[i][j] = A[i] == B[j]? min(E[i - 1][j - 1], D[i - 1][j - 1]) : inf;
            D[i][j] = min(E[i][j - 1] + 1, D[i][j - 1]);
        }
    }
    int ans = min(E[n - 1][m - 1], D[n - 1][m - 1]);
    cout << (ans < inf? ans : -1);

    return 0;
}
