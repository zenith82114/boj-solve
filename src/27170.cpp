/*
 * Q27170 - Lazy segment tree
 * Date: 2023.3.3
 */

#include<bits/stdc++.h>
using namespace std;

class LazySegTree {
    int N, lgN;
    vector<int> ar, lz;
    void apply(int i, int x) {
        ar[i] += x;
        if (i < N) lz[i] += x;
    }
    void push(int i) {
        apply(i<<1, lz[i]);
        apply(i<<1|1, lz[i]);
        lz[i] = 0;
    }
    void pull(int i) {
        ar[i] = min(ar[i<<1], ar[i<<1|1]);
    }
public:
    LazySegTree(int sz) {
        for (N = 1, lgN = 0; N < sz; N <<= 1, ++lgN);
        ar.resize(N<<1, 0);
        lz.resize(N, 0);

        iota(ar.begin() + N, ar.end(), 0);
        for (int i = N-1; i; --i) ar[i] = ar[i<<1];
    }
    void add(int i, int j, int x) {
        i |= N, j |= N;
        for (int k = lgN; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, x);
            if (~r&1) apply(r--, x);
        }
        for (int k = 1; k <= lgN; ++k) {
            if     (i>>k<<k != i)   pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    int query() {
        int i = 1, l = 0, r = N-1;
        while (l != r) {
            push(i);
            int m = (l + r)>>1;
            if (ar[i<<1|1]) { i <<= 1; r = m; }
            else { i = i<<1|1; l = m+1; }
        }
        return l;
    }
};

class SegTree {
    int N;
    vector<list<int>> ar;
public:
    SegTree(int sz) {
        for (N = 1; N < sz; N <<= 1);
        ar.resize(N<<1);
    }
    void insert(int i, int j, int x) {
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ar[i++].emplace_back(x);
            if (~j&1) ar[j--].emplace_back(x);
        }
    }
    list<int> query(int i) {
        list<int> li;
        for (i |= N; i; i >>= 1) {
            if (li.size() < ar[i].size()) swap(li, ar[i]);
            li.splice(li.end(), ar[i]);
        }
        return li;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;

    vector<pair<int, int>> req(N+1);
    LazySegTree segt1(N+1);
    SegTree segt2(N+1);
    vector<bool> matched(N+1, false);

    for (int n = 1; n <= N; ++n) {
        auto& [i, j] = req[n]; cin >> i >> j;
        segt1.add(i, j, -1);
        segt2.insert(i, j, n);

        int x = segt1.query();
        if (x) {
            auto li = segt2.query(x);
            vector<int> group;
            for (int& m : li) if (!matched[m]) {
                matched[m] = true;
                segt1.add(req[m].first, req[m].second, 1);
                group.emplace_back(m);
            }

            sort(group.begin(), group.end());
            cout << group.size();
            for (int& m : group) cout << ' ' << m;
            cout << '\n';
        }
        else cout << "0\n";
    }

    return 0;
}
