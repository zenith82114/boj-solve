/*
 * Q1648a - DP
 * Date: 2022.1.12
 */

#include<iostream>
#include<array>
#include<vector>
using namespace std;

constexpr int P = 9901;
int N, M, K;
array<int, (1<<14)> prv, nxt;
array<vector<int>, (1<<14)> map;

// v must contain all integers that can be obtained by
// replacing one or more 00(s) in k at position i or higher with 11
void buildMap(vector<int>& v, int k, int i) {
    v.push_back(k);
    for (int t = (3<<i); t < K; i++, t <<= 1) {
        if (!(k & t))
            buildMap(v, k | t, i+2);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    if (N & M & 1) {
        cout << 0 << '\n';
        return 0;
    }
    // time = O(N*(2^M))
    if (N < M)
        swap(N, M);
    K = 1 << M;

    for (int k = 0; k < K; k++)
        buildMap(map[k], k, 0);

    for (int k = 0; k < K-1; k++)
        nxt[k] = 0;
    nxt[K-1] = 1;
    for (int n = 0; n < N; n++) {
        // Incoming vertical in row n = outgoing vertical in row n-1
        for (int k = 0; k < K; k++) {
            prv[k ^ (K-1)] = nxt[k];
            nxt[k] = 0;
        }
        // Combine # ways to use horizontals in row n
        // Cells uncovered here will be covered with outgoing verticals
        for (int k = 0; k < K; k++) {
            if (prv[k]) {
                for (int& l : map[k])
                    nxt[l] += prv[k];
            }
            nxt[k] %= P;
        }
    }

    cout << nxt[K-1] << '\n';
    return 0;
}
