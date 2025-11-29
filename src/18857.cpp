/*
 * Q18857 - block-cut tree
 * Date: 2025.11.28
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using ii = pair<int, int>;
constexpr int MAXN = 404040;
constexpr int INF = 1e9;

struct edge_t {
    int x, y, w;
    edge_t(int x, int y, int w): x(x), y(y), w(w) {}
};

vector<ii> graph[MAXN];
vector<int> bct[2*MAXN];
vector<edge_t> block_edges[2*MAXN];

array<int, MAXN> dfn, low;
stack<edge_t> stk;
int block_id;

void dfs(int p, int x) {
    static int clk = 0;
    dfn[x] = low[x] = ++clk;

    for (auto [y, w] : graph[x]) if (y != p) {
        if (dfn[y]) {
            low[x] = min(low[x], dfn[y]);
            if (dfn[y] < dfn[x]) stk.emplace(x, y, w);
        }
        else {
            stk.emplace(x, y, w);
            dfs(x, y);
            low[x] = min(low[x], low[y]);

            if (dfn[x] <= low[y]) {
                block_id++;
                set<int> block_nodes;

                while (true) {
                    auto [u, v, w] = stk.top(); stk.pop();
                    block_edges[block_id].emplace_back(u, v, w);
                    block_nodes.emplace(u);
                    block_nodes.emplace(v);
                    if (u == x && v == y) break;
                }
                for (int u : block_nodes) {
                    bct[u].emplace_back(block_id);
                    bct[block_id].emplace_back(u);
                }
            }
        }
    }
}

int cut_block(int id, int u, int v) {
    const auto& edges = block_edges[id];

    if (edges.size() == 1) return edges[0].w;

    map<int, vector<ii> > local_graph;
    for (auto [x, y, w] : edges) {
        local_graph[x].emplace_back(y, w);
        local_graph[y].emplace_back(x, w);
    }

    set<ii> path1;
    map<int, ii> pred;
    pred[u] = make_pair(0, 0);

    queue<int> q; q.emplace(u);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (x == v) break;
        for (auto [y, w] : local_graph[x]) {
            if (pred.find(y) == pred.end()) {
                pred[y] = make_pair(x, w);
                q.emplace(y);
            }
        }
    }

    int w1 = INF;
    for (int y = v; y != u;) {
        auto [x, w] = pred[y];
        path1.emplace(min(x, y), max(x, y));
        w1 = min(w1, w);
        y = x;
    }

    int w2 = INF;
    for (auto [x, y, w] : edges) {
        ii e(min(x, y), max(x, y));
        if (!path1.count(e)) w2 = min(w2, w);
    }

    return w1 + w2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        graph[x].emplace_back(y, w);
        graph[y].emplace_back(x, w);
    }
    dfn.fill(0);
    block_id = n;
    dfs(0, 1);

    queue<int> q; q.emplace(1);
    vector<int> pred(block_id + 1, 0);
    vector<bool> vis(block_id + 1, false); vis[1] = true;

    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : bct[x]) if (!vis[y]) {
            vis[y] = true;
            pred[y] = x;
            q.emplace(y);
        }
    }

    int ans = INF;
    for (int y = n; y != 1;) {
        int x = pred[y];
        if (x > n) {
            ans = min(ans, cut_block(x, pred[x], y));
            y = pred[x];
        }
        else y = x;
    }

    cout << ans;
    return 0;
}
