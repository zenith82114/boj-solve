/*
 * Q25564 - Manacher's alg. + suffix/LCP arrays
 * Date: 2023.7.5
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, K; cin >> N >> K;
    string S; cin >> S;
    string T = "$";
    for (auto c : S) {
        T.push_back(c);
        T.push_back('$');
    }

    const int M = 2*N + 1;
    vector<int> rad(M);
    int i = 0, r = 0;
    while (i < M) {
        while (i-r-1 >= 0 && i+r+1 < M && T[i-r-1] == T[i+r+1]) ++r;
        rad[i] = r;
        int rj, s;
        for (rj = i+1; rj <= i+r; ++rj) {
            int lj = 2*i - rj;
            s = i+r - rj;
            if (rad[lj] != s) rad[rj] = min(rad[lj], s);
            else break;
        }
        r = (rj <= i+r? s : 0);
        i = rj;
    }

    vector<pair<int, int> > v;
    const int ke = K&1? K+1 : K;
    const int ko = K&1? K : K+1;
    for (int i = 0; i < M; ++i) {
        if ((~i&1) && rad[i] >= ke)
            v.emplace_back((i - ke)/2, (i + ke)/2 -1);
        else if ((i&1) && rad[i] >= ko)
            v.emplace_back((i - ko)/2, (i + ko)/2 -1);
    }
    sort(v.begin(), v.end());

    vector<int> pe(N, N);
    i = 0;
    for (auto& [l, r] : v) {
        while (i <= l) pe[i++] = r;
    }

    vector<int> rnk(N<<1);
    vector<int> cnt(128);
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

        auto cmp = [&] (int a, int b) -> int {
            return rnk[a] < rnk[b] || (rnk[a] == rnk[b] && rnk[a+d] < rnk[b+d]);
        };
        vector<int> nrnk(N<<1);
        nrnk[sa[0]] = 1;
        for (i = 1; i < N; ++i)
            nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
        if (nrnk[sa[N-1]] == N) break;
        swap(rnk, nrnk);
    }

    vector<int> isa(N);
    for (i = 0; i < N; ++i) isa[sa[i]] = i;

    vector<int> lcp(N);
    for (int k = 0, i = 0; i < N; ++i) if (isa[i]) {
        int j = sa[isa[i]-1];
        while (i+k < N && j+k < N && S[i+k] == S[j+k]) ++k;
        lcp[isa[i]] = k? k-- : 0;
    }

    int64_t ans = N - pe[0];
    for (int i = 1; i < N; ++i) {
        ans += N - pe[i];
        if (sa[i] + lcp[i] > pe[sa[i]])
            ans -= sa[i] + lcp[i] - pe[sa[i]];
    }
    cout << ans;
    return 0;
}
