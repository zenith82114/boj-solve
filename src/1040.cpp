/*
 * Q1040 - DP
 * Date: 2022.3.19
 */

#include<bits/stdc++.h>
using namespace std;

string N, M;
int K, lN;
bool memo[20][1<<10][2];

bool dfs(int i, int k, int mask, bool tight) {
    if (i == lN) return k == K;
    if (memo[i][mask][tight]) return false;

    bool flag = false;
    for (char d = tight ? N[i] : '0'; d <= '9'; ++d) {
        int md = 1 << (d - '0');
        if (!(mask & md)) {
            if (k < K) {
                flag = true;
                mask |= md;
                ++k;
            }
            else continue;
        }
        M[i] = d;
        if (dfs(i+1, k, mask, tight && d == N[i])) return true;
        if (flag) {
            flag = false;
            mask ^= md;
            --k;
        }
    }
    M[i] = '0';
    memo[i][mask][tight] = true;
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    lN = N.size();
    M.resize(lN, '0');
    if (lN < K || !dfs(0, 0, 0, true)) {
        int lM = max(lN +1, K);
        M.resize(lM, '0');
        M[0] = '1';
        for (int k = 2; k < K; ++k)
            M[lM - K + k] = k + '0';
    }
    cout << M << '\n';
    return 0;
}
