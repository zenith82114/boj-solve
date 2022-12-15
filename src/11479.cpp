/*
 * Q11479 - Distinct substrings w/ suffix array, LCP array
 * Date: 2022.2.7
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string S; cin >> S;
    int N = S.length();

    // Manber-Myers alg.
    vector<int> sa(N), rnk(N<<1), nrnk(N<<1), tmp(N);
    int M = max(N+1, 256);
    vector<int> cnt(M);

    for (int i = 0; i < N; ++i)
        sa[i] = i, rnk[i] = S[i];
    for (int i, d = 1; d < N; d <<= 1) {
        fill(cnt.begin(), cnt.end(), 0);
        for (i = 0; i < N; ++i) cnt[rnk[i+d]]++;
        for (i = 1; i < M; ++i) cnt[i] += cnt[i-1];
        for (i = N-1; ~i; --i)  tmp[--cnt[rnk[i+d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (i = 0; i < N; ++i) cnt[rnk[i]]++;
        for (i = 1; i < M; ++i) cnt[i] += cnt[i-1];
        for (i = N-1; ~i; --i)  sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        auto cmp = [&](int a, int b) {
            return rnk[a] < rnk[b] || (rnk[a] == rnk[b] && rnk[a+d] < rnk[b+d]);
        };
        nrnk[sa[0]] = 1;
        for (i = 1; i < N; ++i)
            nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
        if (nrnk[sa[N-1]] == N) // done early
            break;
        swap(rnk, nrnk);
    }

    // Kasai's alg.
    vector<int> isa(N);
    for (int i = 0; i < N; ++i) isa[sa[i]] = i;

    vector<int> lcp(N);
    ulong ans = (1ul * N * (N+1))>>1;
    for (int j, k = 0, i = 0; i < N; ++i) {
        if (!isa[i])
            continue;
        j = sa[isa[i]-1];
        while (S[i+k] == S[j+k])
            k++;
        lcp[isa[i]] = (k ? k-- : 0);
        ans -= lcp[isa[i]];
    }

    cout << ans << '\n';
    return 0;
}
