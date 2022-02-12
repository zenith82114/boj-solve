/*
 * Q13548 - Mo's alg.
 * Date: 2022.2.12
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> A;
struct Query { int id, l, r; };
vector<Query> Q;
vector<int> R;
array<int, 1'000'001> freq;
vector<int> freqGroup;
int maxFreq;

inline void add(int x) {
    int f = freq[x]++;
    freqGroup[f]--;
    freqGroup[f+1]++;
    if (maxFreq == f)
        maxFreq++;
}
inline void remove(int x) {
    int f = freq[x]--;
    freqGroup[f]--;
    freqGroup[f-1]++;
    if (!freqGroup[maxFreq])
        maxFreq--;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M;
    int blk, l, r;

    cin >> N;
    A.resize(N+1);
    for (int n=1; n<=N; n++)
        cin >> A[n];
    cin >> M;
    Q.resize(M);
    for (int m=0; m<M; m++) {
        Q[m].id = m;
        cin >> Q[m].l >> Q[m].r;
    }
    blk = (int)sqrt(N+1);
    sort(Q.begin(), Q.end(), [&](const Query& p, const Query& q){
        return p.r/blk != q.r/blk ? p.r/blk < q.r/blk : p.l < q.l;
    });

    freq.fill(0);
    maxFreq = 0;
    freqGroup.assign(N+1, 0);
    R.resize(M);
    l = 1, r = 0;
    for (auto& q : Q) {
        while (r < q.r)
            add(A[++r]);
        while (r > q.r)
            remove(A[r--]);
        while (l < q.l)
            remove(A[l++]);
        while (l > q.l)
            add(A[--l]);
        R[q.id] = maxFreq;
    }

    for (int& res : R)
        cout << res << '\n';
    return 0;
}
