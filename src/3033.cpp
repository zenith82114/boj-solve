/*
 * Q3033 - Suffix array and LCP array
 * Date: 2022.9.19
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    string S; cin >> S;
    int i;

    vector<int> rnk(N<<1);
    vector<int> cnt(128, 0);
    for (i = 0; i < N; ++i) cnt[S[i]] = 1;
    for (i = 'a'; i < 'z'; ++i) cnt[i+1] += cnt[i];
    for (i = 0; i < N; ++i) rnk[i] = cnt[S[i]];
    cnt.resize(N+1);

    vector<int> sa(N);

    for (int d = 1; d < N; d <<= 1) {
        vector<int> tmp(N, 0);

        fill(cnt.begin(), cnt.end(), 0);
        for (i = 0; i < N; ++i) ++cnt[rnk[i+d]];
        for (i = 1; i < N; ++i) cnt[i] += cnt[i-1];
        for (i = N-1; ~i; --i) tmp[--cnt[rnk[i+d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (i = 0; i < N; ++i) ++cnt[rnk[i]];
        for (i = 1; i < N; ++i) cnt[i] += cnt[i-1];
        for (i = N-1; ~i; --i) sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        auto cmp = [&](int a, int b) {
            return rnk[a] < rnk[b] ||
            (rnk[a] == rnk[b] && rnk[a+d] < rnk[b+d]);
        };
        vector<int> nrnk(N<<1);
        nrnk[sa[0]] = 1;
        for (i = 1; i < N; ++i)
            nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
        if (nrnk[sa[N-1]] == N)
            break;
        swap(rnk, nrnk);
    }

    vector<int> isa(N);
    for (i = 0; i < N; ++i) isa[sa[i]] = i;

    vector<int> lcp(N);
    for (int k = 0, i = 0; i < N; ++i) if (isa[i]) {
        int j = sa[isa[i]-1];
        while (S[i+k] == S[j+k]) ++k;
        lcp[isa[i]] = k? k-- : 0;
    }

    int ans = 0;
    for (const int &l : lcp) ans = max(ans, l);
    cout << ans << '\n';

    return 0;
}
