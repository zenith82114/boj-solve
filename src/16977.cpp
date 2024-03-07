/*
 * Q16977 - Parallel binary search + segment tree (maximum subarray sum)
 * Date: 2024.3.7
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
using iii = tuple<int, int, int>;

class SegTree {
    struct node {
        i64 t, p, s, a;
        node(i64 x): t{x}, p{x}, s{x}, a{x} {}
        node operator+(const node& rhs) const {
            node ans(0);
            ans.t = t + rhs.t;
            ans.p = max(p, t + rhs.p);
            ans.s = max(s + rhs.t, rhs.s);
            ans.a = max({a, rhs.a, s + rhs.p});
            return ans;
        }
    };
    vector<node> ar;
    int n;
    stack<int> lst, rst;
public:
    SegTree(int sz) {
        n = 1; while (n < sz) n <<= 1;
        ar.resize(n<<1, 0);
    }
    void init() {
        for (int i = n; i < 2*n; ++i) ar[i] = node(-n);
        for (int i = n-1; i; --i) ar[i] = ar[i<<1] + ar[i<<1|1];
    }
    void update(int i, i64 x) {
        ar[i |= n] = node(x);
        for (i >>= 1; i; i >>= 1) ar[i] = ar[i<<1] + ar[i<<1|1];
    }
    i64 query(int i, int j) {
        for (i |= n, j |= n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) lst.emplace(i++);
            if (~j&1) rst.emplace(j--);
        }
        node ans(0);
        for (; !lst.empty(); lst.pop()) { ans = ar[lst.top()] + ans; }
        for (; !rst.empty(); rst.pop()) { ans = ans + ar[rst.top()]; }
        return ans.a;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N; cin >> N;
    vector<ii> v;
    vector<int> hs;
    for (int i = 1; i <= N; ++i) {
        int h; cin >> h;
        v.emplace_back(h, i);
        hs.emplace_back(h);
    }
    sort(v.begin(), v.end(), greater<ii>());

    sort(hs.begin(), hs.end());
    hs.erase(unique(hs.begin(), hs.end()), hs.end());
    for (auto& [h, i] : v) {
        h = lower_bound(hs.begin(), hs.end(), h) - hs.begin();
    }
    const int H = hs.size();

    int Q; cin >> Q;
    vector<iii> que(Q);
    for (auto& [l, r, w] : que) cin >> l >> r >> w;

    vector<ii> ans(Q);
    for (auto& [lo, hi] : ans) lo = 0, hi = H;

    vector<vector<int> > bucket(H);

    SegTree segt(N+1);

    bool again = true;
    while (again) {
        for (auto& bkt : bucket) bkt.clear();
        for (int q = 0; q < Q; ++q) {
            const auto& [lo, hi] = ans[q];
            if (lo < hi) bucket[(lo+hi)>>1].emplace_back(q);
        }

        again = false;
        segt.init();

        for (int st = 0, en = 0; st < N; st = en) {
            while (en < N && v[st].first == v[en].first) ++en;
            for (int k = st; k < en; ++k) {
                const auto& [h, i] = v[k];
                segt.update(i, 1);
            }

            int h = v[st].first;
            for (int q : bucket[h]) {
                const auto& [l, r, w] = que[q];
                int ret = segt.query(l, r);
                auto& [lo, hi] = ans[q];
                if (ret < w) hi = h;
                else lo = h+1;
                again = again || (lo < hi);
            }
        }
    }

    for (const auto& [lo, hi] : ans) cout << hs[lo-1] << '\n';
    return 0;
}
