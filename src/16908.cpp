/*
 * Q16908 - suffix/LCP arrays, two pointers, sliding window min/max with deque
 * Date: 2025.12.25
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        string t; cin >> t;
        s.append(t);
        s.push_back((char)i);
    }
    s.pop_back();

    const int n = s.size();
    vector<int> id(n);
    for (int i = 0; i < n; ++i) {
        static int j = 0;
        if (s[i] > m) id[i] = j; else ++j;
    }

    vector<int> cnt(128, 0);
    for (int i = 0; i < n; ++i) cnt[s[i]] = 1;
    partial_sum(begin(cnt), end(cnt), begin(cnt));
    vector<int> rnk(2*n);
    for (int i = 0; i < n; ++i) rnk[i] = cnt[s[i]];
    cnt.resize(n + 1);

    vector<int> sa(n);

    for (int d = 1; d < n; d *= 2) {
        vector<int> tmp(n, 0);

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i + d]];
        partial_sum(begin(cnt), end(cnt), begin(cnt));
        for (int i = n - 1; i > -1; --i) tmp[--cnt[rnk[i + d]]] = i;

        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) ++cnt[rnk[i]];
        partial_sum(begin(cnt), end(cnt), begin(cnt));
        for (int i = n - 1; i > -1; --i) sa[--cnt[rnk[tmp[i]]]] = tmp[i];

        auto cmp = [&](int a, int b) {
            return make_pair(rnk[a], rnk[a + d]) < make_pair(rnk[b], rnk[b + d]);
        };
        vector<int> nrnk(2*n);
        nrnk[sa[0]] = 1;
        for (int i = 1; i < n; ++i) {
            nrnk[sa[i]] = nrnk[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        if (nrnk[sa.back()] == n) break;
        rnk.swap(nrnk);
    }

    vector<int> isa(n);
    for (int i = 0; i < n; ++i) isa[sa[i]] = i;

    vector<int> lcp(n);
    for (int z = 0, i = 0; i < n; ++i) if (isa[i]) {
        int j = sa[isa[i] - 1];
        while (i + z < n && j + z < n && s[i + z] == s[j + z]) ++z;
        lcp[isa[i]] = z? z-- : 0;
    }

    cnt.assign(m, 0);
    int ucnt = 0;
    deque<int> dq;
    int ans = 0;

    for (int s = m - 1, e = m - 1; e < n; ++e) {
        if (++cnt[id[sa[e]]] == 1) ++ucnt;
        while (!dq.empty() && lcp[dq.back()] >= lcp[e]) dq.pop_back();
        dq.push_back(e);

        for (; s < e && ucnt == m; ++s) {
            if (!dq.empty()) ans = max(ans, lcp[dq.front()]);
            if (--cnt[id[sa[s]]] == 0) --ucnt;
            while (!dq.empty() && dq.front() <= s + 1) dq.pop_front();
        }
    }

    cout << ans;
    return 0;
}
