/*
 * Q16911 - offline dynamic connectivity
 * Date: 2025.8.16
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;

struct Interval {
    int x, y, s, e;
    Interval(int x, int y, int s, int e): x(x), y(y), s(s), e(e) {};
};
vector<Interval> intv;
map<ii, int> mp;
vector<ii> que, unions[1<<18];
int dsu[100'004];

int _find(int x) { return dsu[x] < 0? x : _find(dsu[x]); }

bool connected(int x, int y) { return _find(x) == _find(y); }

ii unite(int x, int y) {
    x = _find(x), y = _find(y);
    if (x == y) return {-1, 0};
    if (dsu[x] < dsu[y]) swap(x, y);
    ii log(x, dsu[x]);
    dsu[y] += dsu[x]; dsu[x] = y;
    return log;
}

void rollback(const ii& log) {
    auto [x, v] = log;
    if (x == -1) return;
    int y = dsu[x];
    dsu[y] -= (dsu[x] = v);
}

void add_util(int n, int ns, int ne, const Interval& t) {
    if (t.e <= ns || ne <= t.s) return;
    if (t.s <= ns && ne <= t.e) unions[n].emplace_back(t.x, t.y);
    else {
        int mid = (ns + ne)/2;
        add_util(n<<1, ns, mid, t);
        add_util(n<<1|1, mid, ne, t);
    }
}

void solve_util(int n, int ns, int ne) {
    vector<ii> logs;
    for (const auto& [x, y] : unions[n]) logs.emplace_back(unite(x, y));
    if (ns + 1 == ne) {
        auto [x, y] = que[ns];
        cout << connected(x, y) << '\n';
    } else {
        int mid = (ns + ne)/2;
        solve_util(n<<1, ns, mid);
        solve_util(n<<1|1, mid, ne);
    }
    while (!logs.empty()) { rollback(logs.back()); logs.pop_back(); }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    int q = 0;
    while (m--) {
        int t, x, y; cin >> t >> x >> y;
        if (x > y) swap(x, y);
        ii key(x, y);
        if (t == 1) mp.emplace(key, q);
        else if (t == 2) {
            if (mp[key] < q) intv.emplace_back(x, y, mp[key], q);
            mp.erase(key);
        } else {
            que.emplace_back(x, y);
            ++q;
        }
    }
    for (const auto& [key, v] : mp) {
        auto [x, y] = key;
        intv.emplace_back(x, y, v, q);
    }
    mp.clear();
    for (const auto& t : intv) add_util(1, 0, q, t);
    memset(dsu, -1, sizeof dsu);
    solve_util(1, 0, q);
    return 0;
}
