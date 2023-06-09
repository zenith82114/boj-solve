/*
 * Q26526 - DP
 * Date: 2023.6.9
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    static constexpr int MOD = 1'000'000'007;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {}

    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
};

mint f[3001][3001];
mint D[3001][3001];
mint H[3001][3001];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, K; cin >> N >> K;
    f[1][0] = 1;
    D[1][0] = 1;

    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= K; ++j) {
            if (i > j) f[i][j] = D[i-1][j-1] + H[i-j][K-j];
            D[i][j] += D[i-1][j-1] + f[i][j];
            H[i][j] += H[i][j-1] + f[i][j];
        }
    }

    cout << H[N][K].val;
    return 0;
}
