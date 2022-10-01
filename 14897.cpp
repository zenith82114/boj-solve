/*
 * Q14897 - Mo's alg.
 * Date: 2022.10.2
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    using pii = pair<int, int>;

    int N; cin >> N;
    vector<pii> ar(N);
    for (int i = 0; i < N; ++i) {
        ar[i].first = i;
        cin >> ar[i].second;
    }
    sort(ar.begin(), ar.end(), [](const pii &a, const pii &b) {
        return a.second < b.second;
    });
    for (int i = 0, j = -1, prev = 0; i < N; ++i) {
        if (prev < ar[i].second) ++j;
        prev = ar[i].second;
        ar[i].second = j;
    }
    const int M = ar.back().second + 1;
    sort(ar.begin(), ar.end());

    int Q; cin >> Q;
    struct query { int id, l, r; };
    vector<query> que(Q);
    for (int i = 0; i < Q; ++i) {
        auto &q = que[i];
        q.id = i;
        cin >> q.l >> q.r; --q.l; --q.r;
    }
    const int K = (int)sqrt(N);
    sort(que.begin(), que.end(), [&](const query &a, const query &b) {
        if (a.l/K != b.l/K) return a.l < b.l;
        return ((a.l/K) & 1)? (a.r > b.r) : (a.r < b.r);
    });

    vector<int> freq(M);
    vector<int> ans(Q);
    int l = 0, r = -1;
    int cnt = 0;
    for (auto q : que) {
        while (l > q.l) {
            int &f = freq[ar[--l].second];
            if (!f) ++cnt;
            ++f;
        }
        while (r < q.r) {
            int &f = freq[ar[++r].second];
            if (!f) ++cnt;
            ++f;
        }
        while (l < q.l) {
            int &f = freq[ar[l++].second];
            --f;
            if (!f) --cnt;
        }
        while (r > q.r) {
            int &f = freq[ar[r--].second];
            --f;
            if (!f) --cnt;
        }
        ans[q.id] = cnt;
    }

    for (const int &a : ans) cout << a << '\n';
    return 0;
}
