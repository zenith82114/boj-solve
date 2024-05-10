/*
 * Q13513 - LCA + centroid decomposition
 * Date: 2024.5.10
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100005;
constexpr int INF = INT32_MAX/2;
constexpr int nINF = INT32_MIN/2;

int n, tn;
array<vector<pair<int, int> >, MAXN> adj;
vector<int> eut;
array<int, MAXN> dep, lvl, vis;

void make_eut(int px, int x) {
    vis[x] = eut.size();
    eut.emplace_back(x);
    for (const auto& [y, w] : adj[x]) if (y != px) {
        dep[y] = dep[x] + w;
        lvl[y] = lvl[x] + 1;
        make_eut(x, y);
        eut.emplace_back(x);
    }
}

int dist(int x, int y) {
    int l = vis[x], r = vis[y];
    if (l > r) swap(l, r);

    int lca = 0;
    for (l |= tn, r |= tn; l <= r; l >>= 1, r >>= 1) {
        if (l&1) {
            if (lvl[lca] > lvl[eut[l]]) lca = eut[l];
            ++l;
        }
        if (~r&1) {
            if (lvl[lca] > lvl[eut[r]]) lca = eut[r];
            --r;
        }
    }
    return dep[x] + dep[y] - 2*dep[lca];
}

array<int, MAXN> sz, ct_par;
bitset<MAXN> sel;

int get_sz(int px, int x) {
    sz[x] = 1;
    for (const auto& [y, w] : adj[x]) if (y != px && !sel[y]) {
        sz[x] += get_sz(x, y);
    }
    return sz[x];
}

int get_ct(int px, int x, int m) {
    for (const auto& [y, w] : adj[x]) {
        if (y != px && !sel[y] && sz[y] > m) {
            return get_ct(x, y, m);
        }
    }
    return x;
}

void make_ct_tree(int pc, int x) {
    int k = get_sz(pc, x);
    int c = get_ct(pc, x, k/2);
    ct_par[c] = pc;
    sel.set(c);
    for (const auto& [y, w] : adj[c]) if (!sel[y]) make_ct_tree(c, y);
}

bitset<MAXN> white;
int white_cnt;

// way[pc][c] = { dist(pc, x)
//                ; pc, c are parent-child centroids
//                ; x is in CT(c) and white[x] }
// way[pc][pc] = { 0 } if white[pc], { } otherwise
array<map<int, multiset<int> >, MAXN> way;

// way_mx[c] = { max(way[c][*]) }
array<multiset<int>, MAXN> way_mx;

// ans[c] = answer within CT(c)
array<int, MAXN> ans;

// anss = { ans[c] ; ans[c] != nINF }
multiset<int> anss;

void update_ans(int c) {
    if (way_mx[c].size() < 2) {
        if (ans[c] != nINF) anss.erase(anss.find(ans[c]));
        ans[c] = nINF;
        return;
    }
    int tmp = *way_mx[c].rbegin() + *next(way_mx[c].rbegin());
    if (ans[c] == nINF) {
        ans[c] = tmp;
        anss.emplace(tmp);
    }
    else if (ans[c] != tmp) {
        anss.erase(anss.find(ans[c]));
        ans[c] = tmp;
        anss.emplace(tmp);
    }
}

void update(int x) {
    white.flip(x);
    white_cnt += white[x]? 1 : -1;

    int pc = x, c = x;
    if (white[x]) {
        for (; pc != 0; c = pc, pc = ct_par[pc]) {
            int d = dist(pc, x);
            auto& w = way[pc][c];

            if (w.lower_bound(d) == w.end()) {
                if (!w.empty()) {
                    way_mx[pc].erase(way_mx[pc].find(*w.rbegin()));
                }
                way_mx[pc].emplace(d);
                w.emplace(d);
                update_ans(pc);
            } else {
                w.emplace(d);
            }
        }
    } else {
        for (; pc != 0; c = pc, pc = ct_par[pc]) {
            int d = dist(pc, x);
            auto& w = way[pc][c];

            int e = *w.rbegin();
            w.erase(w.find(d));
            if (w.lower_bound(e) == w.end()) {
                way_mx[pc].erase(way_mx[pc].find(e));
                if (!w.empty()) way_mx[pc].emplace(*w.rbegin());
                update_ans(pc);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        adj[x].emplace_back(y, w);
        adj[y].emplace_back(x, w);
    }

    dep[1] = 0;
    lvl[1] = 0;
    tn = 0;
    make_eut(0, 1);

    tn = eut.size();
    while (tn & (tn-1)) tn += tn & (-tn);
    eut.resize(2*tn);
    copy(eut.begin(), eut.begin() + tn, eut.begin() + tn);
    lvl[0] = INF;
    for (int i = tn-1; i > 0; --i) {
        int x = eut[i<<1], y = eut[i<<1|1];
        eut[i] = lvl[x] < lvl[y]? x : y;
    }

    sel.reset();
    make_ct_tree(0, 1);

    white.reset();
    white_cnt = 0;
    ans.fill(nINF);

    for (int x = 1; x <= n; ++x) update(x);

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op&1) {
            int x; cin >> x;
            update(x);
        } else {
            if (white_cnt == 0) cout << -1;
            else if (white_cnt == 1) cout << 0;
            else cout << max(0, *anss.rbegin());
            cout << '\n';
        }
    }

    return 0;
}
