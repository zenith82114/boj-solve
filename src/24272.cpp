/*
 * Q24272 - Euler tour + Boolean segment tree
 * Date: 2023.6.7
 */

#include<bits/stdc++.h>
using namespace std;

array<vector<int>, 100'001> adj;
array<int, 100'001> et, sz;

void dfs(int px, int x, int& clk) {
    et[x] = clk++;
    sz[x] = 1;
    for (int y : adj[x]) if (y != px) {
        dfs(x, y, clk);
        sz[x] += sz[y];
    }
}

class SegTree {
    int N;
    vector<int> cnt, val;
    void add_util(int n, int ns, int ne, int i, int j, int x) {
        int nm = (ns + ne)>>1;
        if (ns > j || ne < i) return;
        if (ns < i || ne > j) {
            add_util(n<<1, ns, nm, i, j, x);
            add_util(n<<1|1, nm+1, ne, i, j, x);
        }
        else cnt[n] += x;
        if (cnt[n]) val[n] = ne - ns + 1;
        else if (ns != ne) val[n] = val[n<<1] + val[n<<1|1];
        else val[n] = 0;
    }
public:
    SegTree(int sz) {
        N = 1; while (N < sz) N *= 2;
        cnt.resize(N*2);
        val.resize(N*2);
    }
    void add(int i, int j, int x) {
        if (i > j) return;
        add_util(1, 0, N-1, i, j, x);
    }
    int query() { return val[1]; }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;

    vector<pair<int, int> > buf;
    for (int i = 1; i < N; ++i) {
        int x, y; string s; cin >> x >> s >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
        if (s[0] == '<') buf.emplace_back(y, x);
        if (s[1] == '>') buf.emplace_back(x, y);
    }

    int clk = 0; dfs(0, 1, clk);

    SegTree segt(N);
    set<pair<int, int> > rec;

    for (const auto& [x, y] : buf) {
        if (sz[x] > sz[y]) segt.add(et[y], et[y] + sz[y] - 1, 1);
        else {
            segt.add(0, et[x] - 1, 1);
            segt.add(et[x] + sz[x], N-1, 1);
        }
        rec.emplace(x, y);
    }

    int Q; cin >> Q;
    while (Q--) {
        int x, y; string s; cin >> x >> s >> y;

        if (rec.find({x, y}) != rec.end()) {
            if (sz[x] > sz[y]) segt.add(et[y], et[y] + sz[y] - 1, -1);
            else {
                segt.add(0, et[x] - 1, -1);
                segt.add(et[x] + sz[x], N-1, -1);
            }
            rec.erase({x, y});
        }
        else if (rec.find({y, x}) != rec.end()) {
            if (sz[y] > sz[x]) segt.add(et[x], et[x] + sz[x] - 1, -1);
            else {
                segt.add(0, et[y] - 1, -1);
                segt.add(et[y] + sz[y], N-1, -1);
            }
            rec.erase({y, x});
        }

        if (s.compare("--")) {
            if (s[0] == '<') swap(x, y);
            if (sz[x] > sz[y]) segt.add(et[y], et[y] + sz[y] - 1, 1);
            else {
                segt.add(0, et[x] - 1, 1);
                segt.add(et[x] + sz[x], N-1, 1);
            }
            rec.emplace(x, y);
        }
        cout << N - segt.query() << '\n';
    }

    return 0;
}
