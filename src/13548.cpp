/*
 * Q13548 - Mo's alg.
 * Date: 2022.2.12
 */

#include<bits/stdc++.h>
using namespace std;

array<int, 1'000'001> freq;
vector<int> freq_group;
int max_freq;

inline void add(int x) {
    int f = freq[x]++;
    freq_group[f]--;
    freq_group[f+1]++;
    if (max_freq == f)
        max_freq++;
}
inline void remove(int x) {
    int f = freq[x]--;
    freq_group[f]--;
    freq_group[f-1]++;
    if (!freq_group[max_freq])
        max_freq--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N+1);
    for (int n = 1; n <= N; ++n) cin >> A[n];

    int M; cin >> M;
    struct query { int id, l, r; };
    vector<query> Q(M);
    for (int m = 0; m < M; ++m) {
        Q[m].id = m;
        cin >> Q[m].l >> Q[m].r;
    }
    int blk = (int)sqrt(N+1);
    sort(Q.begin(), Q.end(), [&blk](const query& p, const query& q){
        return p.r/blk != q.r/blk ? p.r/blk < q.r/blk : p.l < q.l;
    });

    freq.fill(0);
    max_freq = 0;
    freq_group.resize(N+1, 0);
    vector<int> R(M);
    int l = 1, r = 0;
    for (const auto& q : Q) {
        while (r < q.r)
            add(A[++r]);
        while (r > q.r)
            remove(A[r--]);
        while (l < q.l)
            remove(A[l++]);
        while (l > q.l)
            add(A[--l]);
        R[q.id] = max_freq;
    }

    for (const int& res : R)
        cout << res << '\n';
    return 0;
}
