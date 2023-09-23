/*
 * Q13550 - Mo's alg. + square root decomposition
 * Date: 2023.9.23
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

int A[100'001] {};
list<int> lss[1'000'001];
struct query { int id, l, r; } que[100'000];
int ans[100'000];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, K; cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        A[i] = (A[i] + A[i-1]) % K;
    }

    int M; cin >> M;
    for (int i = 0; i < M; ++i) {
        auto& q = que[i];
        q.id = i;
        cin >> q.l >> q.r;
        q.l--;
    }
    const int S = (int)sqrt(N);
    sort(que, que + M, [&S](const query &a, const query &b) {
        if (a.l/S != b.l/S) return a.l < b.l;
        return ((a.l/S) & 1)? (a.r > b.r) : (a.r < b.r);
    });

    Counter cntr(N+1);
    int l = 0, r = -1;
    for (int i = 0; i < M; ++i) {
        const auto& q = que[i];
        while (l > q.l) {
            auto& ls = lss[A[--l]];
            if (!ls.empty()) cntr.remove(ls.back() - ls.front());
            ls.emplace_front(l);
            cntr.add(ls.back() - ls.front());
        }
        while (r < q.r) {
            auto& ls = lss[A[++r]];
            if (!ls.empty()) cntr.remove(ls.back() - ls.front());
            ls.emplace_back(r);
            cntr.add(ls.back() - ls.front());
        }
        while (l < q.l) {
            auto& ls = lss[A[l++]];
            cntr.remove(ls.back() - ls.front());
            ls.pop_front();
            if (!ls.empty()) cntr.add(ls.back() - ls.front());
        }
        while (r > q.r) {
            auto& ls = lss[A[r--]];
            cntr.remove(ls.back() - ls.front());
            ls.pop_back();
            if (!ls.empty()) cntr.add(ls.back() - ls.front());
        }
        ans[q.id] = cntr.find_max();
    }

    for (int i = 0; i < M; ++i) cout << ans[i] << '\n';
    return 0;
}
