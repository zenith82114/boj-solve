/*
 * Q13545 - Mo's alg. + Square root decomposition
 * Date: 2022.12.23
 */

#include<bits/stdc++.h>
using namespace std;

class Counter {
    int N, B;
    vector<int> cnt, bin_cnt;
public:
    Counter(int sz) {
        B = (int)sqrt(sz);
        N = (sz + B-1) / B * B;
        cnt.resize(N);
        bin_cnt.resize(N/B);
    }
    void add(int x) {
        cnt[x]++;
        bin_cnt[x/B]++;
    }
    void remove(int x) {
        cnt[x]--;
        bin_cnt[x/B]--;
    }
    int find_max() {
        for (int i = N/B -1; i > -1; --i) if (bin_cnt[i]) {
            for (int j = B-1; j > -1; --j)
                if (cnt[i*B + j]) return i*B + j;
        }
        return -1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N+1);
    int Amin = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        A[i] += A[i-1];
        Amin = min(Amin, A[i]);
    }
    if (Amin < 0) for (int& a : A) a -= Amin;

    int M; cin >> M;
    struct query { int id, l, r; };
    vector<query> que(M);
    for (int i = 0; i < M; ++i) {
        auto& q = que[i];
        q.id = i;
        cin >> q.l >> q.r;
        q.l--;
    }
    const int S = (int)sqrt(N);
    sort(que.begin(), que.end(), [&S](const query &a, const query &b) {
        if (a.l/S != b.l/S) return a.l < b.l;
        return ((a.l/S) & 1)? (a.r > b.r) : (a.r < b.r);
    });

    vector<deque<int>> dqs(N+1);
    Counter cntr(N+1);
    vector<int> ans(M);
    int l = 0, r = -1;
    for (const auto& q : que) {
        while (l > q.l) {
            auto& dq = dqs[A[--l]];
            if (!dq.empty()) cntr.remove(dq.back() - dq.front());
            dq.emplace_front(l);
            cntr.add(dq.back() - dq.front());
        }
        while (r < q.r) {
            auto& dq = dqs[A[++r]];
            if (!dq.empty()) cntr.remove(dq.back() - dq.front());
            dq.emplace_back(r);
            cntr.add(dq.back() - dq.front());
        }
        while (l < q.l) {
            auto& dq = dqs[A[l++]];
            cntr.remove(dq.back() - dq.front());
            dq.pop_front();
            if (!dq.empty()) cntr.add(dq.back() - dq.front());
        }
        while (r > q.r) {
            auto& dq = dqs[A[r--]];
            cntr.remove(dq.back() - dq.front());
            dq.pop_back();
            if (!dq.empty()) cntr.add(dq.back() - dq.front());
        }
        ans[q.id] = cntr.find_max();
    }

    for (const int& a : ans) cout << a << '\n';
    return 0;
}
