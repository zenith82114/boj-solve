/*
 * Q13988 - Segment tree + flood fill
 * Date: 2024.2.10
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class SegTree {
    ii (*comp)(const ii&, const ii&);
    vector<ii> ar;
    int n, nil;
public:
    SegTree(int sz) {
        n = 1; while (n < sz) n <<= 1;
        ar.resize(n<<1);
    }
    void set_comp(ii (*func)(const ii&, const ii&), int x) {
        comp = func;
        nil = x;
    }
    void init(const vector<int>& dat) {
        int sz = dat.size();
        for (int i = 0; i < sz; ++i) {
            ar[i|n] = make_pair(dat[i], i);
        }
        for (int i = n-1; i; --i) {
            ar[i] = comp(ar[i<<1], ar[i<<1|1]);
        }
    }
    void upd(int i, int x) {
        ar[i |= n].first = x;
        for (i >>= 1; i; i >>= 1) {
            ar[i] = comp(ar[i<<1], ar[i<<1|1]);
        }
    }
    ii qry(int i, int j) {
        ii ans(nil, -1);
        for (i += n, j += n; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = comp(ans, ar[i++]);
            if (~j&1) ans = comp(ans, ar[j--]);
        }
        return ans;
    }
};

ii ii_min(const ii& a, const ii& b) { return min(a, b); }
ii ii_max(const ii& a, const ii& b) { return max(a, b); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;

    struct mine { int x, l, r, id; };
    vector<mine> mines(n);
    for (int i = 0; i < n; ++i) {
        auto& [x, l, r, id] = mines[i];
        cin >> x >> l >> r;
        l = x - l;
        r = x + r;
        id = i;
    }

    SegTree segt(n);
    vector<int> dat(n);
    stack<int> stk;
    bitset<1'000'000> vis;
    vector<ii> cover(n);

    segt.set_comp(ii_max, INT32_MIN);
    sort(mines.begin(), mines.end(), [] (const mine& a, const mine& b) {
        return a.l < b.l;
    });
    for (int i = 0; i < n; ++i) dat[i] = mines[i].r;
    segt.init(dat);

    for (int i = 0; i < n; ++i) if (!vis[i]) {
        stk.emplace(i); vis.set(i);
        segt.upd(i, INT32_MIN);
        cover[mines[i].id].first = mines[i].l;
        while (!stk.empty()) {
            int u = stk.top();
            int p = 0, q = n;
            while (p < q) {
                int mid = (p + q)>>1;
                if (mines[u].x < mines[mid].l) q = mid;
                else p = mid+1;
            }
            auto [vr, v] = segt.qry(0, p-1);
            if (vr < mines[u].x) stk.pop();
            else {
                stk.emplace(v); vis.set(v);
                segt.upd(v, INT32_MIN);
                cover[mines[v].id].first = mines[i].l;
            }
        }
    }

    segt.set_comp(ii_min, INT32_MAX);
    sort(mines.begin(), mines.end(), [] (const mine& a, const mine& b) {
        return a.r > b.r;
    });
    for (int i = 0; i < n; ++i) dat[i] = mines[i].l;
    segt.init(dat);
    vis.reset();

    for (int i = 0; i < n; ++i) if (!vis[i]) {
        stk.emplace(i); vis.set(i);
        segt.upd(i, INT32_MAX);
        cover[mines[i].id].second = mines[i].r;
        while (!stk.empty()) {
            int u = stk.top();
            int p = 0, q = n;
            while (p < q) {
                int mid = (p + q)>>1;
                if (mines[u].x > mines[mid].r) q = mid;
                else p = mid+1;
            }
            auto [vl, v] = segt.qry(0, p-1);
            if (vl > mines[u].x) stk.pop();
            else {
                stk.emplace(v); vis.set(v);
                segt.upd(v, INT32_MAX);
                cover[mines[v].id].second = mines[i].r;
            }
        }
    }

    vector<ii> evt;
    for (int i = 0; i < n; ++i) {
        evt.emplace_back(cover[i].first, -1);
        evt.emplace_back(cover[i].second, m);
    }
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        evt.emplace_back(x, i);
    }
    sort(evt.begin(), evt.end());

    vector<int> ans(m);
    int cur = 0;
    for (const auto& [x, tag] : evt) {
        if (tag == -1) ++cur;
        else if (tag == m) --cur;
        else ans[tag] = cur;
    }
    for (int a : ans) cout << a << '\n';
    return 0;
}
