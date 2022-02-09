/*
 * Q11479 - Distinct substrings w/ suffix array, LCP array
 * Date: 2022.2.7
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> sa, isa, lcp;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<int> rnk, nrnk, cnt, tmp;
    string S;
    ulong ans;
    int N, M;

    cin >> S;
    N = S.length();

    // Manber-Myers alg.
    sa.resize(N);
    rnk.assign(N<<1, 0);
    nrnk.assign(N<<1, 0);
    M = max(N+1, 256);
    cnt.resize(M);
    tmp.resize(N);

    for (int i=0; i<N; i++)
        sa[i] = i, rnk[i] = S[i];
    for (int i, d=1; d<N; d<<=1) {
        fill(cnt.begin(), cnt.end(), 0);
        for (i=0; i<N; i++)
            cnt[rnk[i+d]]++;
        for (i=1; i<M; i++)
            cnt[i] += cnt[i-1];
        for (i=N-1; ~i; i--)
            tmp[--cnt[rnk[i+d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (i=0; i<N; i++)
            cnt[rnk[i]]++;
        for (i=1; i<M; i++)
            cnt[i] += cnt[i-1];
        for (i=N-1; ~i; i--)
            sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        auto cmp = [&](int a, int b) {
            return rnk[a]<rnk[b] || (rnk[a]==rnk[b] && rnk[a+d]<rnk[b+d]);
        };
        nrnk[sa[0]] = 1;
        for (i=1; i<N; i++)
            nrnk[sa[i]] = nrnk[sa[i-1]] + cmp(sa[i-1], sa[i]);
        if (nrnk[sa[N-1]] == N) // done early
            break;
        swap(rnk, nrnk);
    }

    // Kasai's alg.
    isa.resize(N);
    for (int i=0; i<N; i++)
        isa[sa[i]] = i;

    lcp.resize(N);
    ans = ((ulong)N*(N+1))>>1;
    for (int j, k=0, i=0; i<N; i++) {
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
