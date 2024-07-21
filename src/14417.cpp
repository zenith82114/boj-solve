/*
 * Q14417 - Manacher's, segment tree, offline queries
 * Date: 2024.7.21
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 200005> rho;
array<vector<pair<int, int> >, 200005> que;
array<int, 100005> ans;

constexpr int tn = 1<<18;
array<int, tn*2> segt;
void segt_ins(int i) {
    for (i |= tn; i; i >>= 1) segt[i]++;
}
int segt_qry(int i) {
    int ret = 0;
    for (int l = tn, r = i|tn; l <= r; l >>= 1, r >>= 1) {
        if ( l&1) ret += segt[l++];
        if (~r&1) ret += segt[r--];
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    string t {'$'};
    for (char c : s) { t.push_back(c); t.push_back('$'); }

    const int n = t.size();
    int i = 0, r = 0;
    while (i < n) {
        while (i-r-1 >= 0 && i+r+1 < n && t[i-r-1] == t[i+r+1]) ++r;
        rho[i] = r;
        int rj, s;
        for (rj = i+1; rj <= i+r; ++rj) {
            int lj = 2*i - rj;
            s = i+r - rj;
            if (rho[lj] != s) rho[rj] = min(rho[lj], s);
            else break;
        }
        r = (rj <= i+r ? s : 0);
        i = rj;
    }

    int q; cin >> q;
    for (int qnum = 0; qnum < q; ++qnum) {
        int idx, len; cin >> idx >> len;
        int pos = 2*idx + len;
        if (pos < n) que[pos].emplace_back(qnum, 2*idx);
        else ans[qnum] = 0;
    }

    segt.fill(0);
    for (int pos = n-1; pos >= 0; --pos) {
        segt_ins(pos - rho[pos]);
        for (auto [qnum, target] : que[pos]) ans[qnum] = segt_qry(target);
    }

    for (int qnum = 0; qnum < q; ++qnum) cout << ans[qnum] << '\n';
    return 0;
}
