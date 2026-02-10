/*
 * Q7149 - segment tree, flood fill
 * Date: 2026.2.10
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
const int MAXN = 1e5 + 4;

class segment_tree {
    static const int n = 1<<17;
    ii (*comp)(const ii&, const ii&);
    ii ar[2*n];
    int nil;
public:
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
} segt;

ii ii_min(const ii& a, const ii& b) { return min(a, b); }
ii ii_max(const ii& a, const ii& b) { return max(a, b); }

struct can { int x, l, r, id; } cans[MAXN];
vector<int> payload;
stack<int> stk;
bitset<MAXN> vis;
ii cover[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    for (cin >> n; n; cin >> n) {
        for (int i = 0; i < n; ++i) {
            auto& [x, l, r, id] = cans[i];
            cin >> x >> r;
            l = x - r;
            r = x + r;
            id = i;
        }

        payload.resize(n);
        segt.set_comp(ii_max, INT32_MIN);
        sort(cans, cans + n, [] (const can& a, const can& b) { return a.l < b.l; });
        for (int i = 0; i < n; ++i) payload[i] = cans[i].r;
        segt.init(payload);
        vis.reset();

        for (int i = 0; i < n; ++i) if (!vis[i]) {
            stk.emplace(i); vis.set(i);
            segt.upd(i, INT32_MIN);
            cover[cans[i].id].first = cans[i].l;
            while (!stk.empty()) {
                int u = stk.top();
                int lo = 0, hi = n;
                while (lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    (cans[u].x >= cans[mid].l ? lo : hi) = mid;
                }
                auto [vr, v] = segt.qry(0, lo);
                if (vr < cans[u].x) stk.pop();
                else {
                    stk.emplace(v); vis.set(v);
                    segt.upd(v, INT32_MIN);
                    cover[cans[v].id].first = cans[i].l;
                }
            }
        }

        segt.set_comp(ii_min, INT32_MAX);
        sort(cans, cans + n, [] (const can& a, const can& b) { return a.r > b.r; });
        for (int i = 0; i < n; ++i) payload[i] = cans[i].l;
        segt.init(payload);
        vis.reset();

        for (int i = 0; i < n; ++i) if (!vis[i]) {
            stk.emplace(i); vis.set(i);
            segt.upd(i, INT32_MAX);
            cover[cans[i].id].second = cans[i].r;
            while (!stk.empty()) {
                int u = stk.top();
                int lo = 0, hi = n;
                while (lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    (cans[u].x <= cans[mid].r ? lo : hi) = mid;
                }
                auto [vl, v] = segt.qry(0, lo);
                if (vl > cans[u].x) stk.pop();
                else {
                    stk.emplace(v); vis.set(v);
                    segt.upd(v, INT32_MAX);
                    cover[cans[v].id].second = cans[i].r;
                }
            }
        }

        vector<int> xs(n);
        for (int i = 0; i < n; ++i) xs[i] = cans[i].x;
        sort(xs.begin(), xs.end());
        for (int i = 0; i < n; ++i) {
            cout << (upper_bound(xs.begin(), xs.end(), cover[i].second)
                - lower_bound(xs.begin(), xs.end(), cover[i].first)) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
