/*
 * Q7626 - Union area of rectangles using sweep line + segment tree
 * Date: 2022.1.6
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct Edge {
    bool is_left;
    int x;
    int y1, y2;
    bool operator<(const Edge &e) {
        return x < e.x;
    }
};
vector<Edge> edges;

// coordinate compression
vector<int> Ys;
int y_to_idx(int y) {
    return distance(Ys.begin(), lower_bound(Ys.begin(), Ys.end(), y));
}
int idx_to_y(int i) {
    return Ys[i];
}

class seg_tree {
    int N;
    vector<int> cnt, len;
    int lc(int n) { return n << 1; }
    int rc(int n) { return n << 1 | 1; }
    void add_range_util(int n, int l, int r, int i, int j, int k) {
        int m = (l + r) >> 1;
        if (l > j || r < i)
            return;
        if (l < i || r > j) {
            add_range_util(lc(n), l, m, i, j, k);
            add_range_util(rc(n), m+1, r, i, j, k);
        }
        else cnt[n] += k;
        if (cnt[n])
            len[n] = idx_to_y(r+1) - idx_to_y(l);
        else if (l != r)
            len[n] = len[lc(n)] + len[rc(n)];
        else
            len[n] = 0;
    }
public:
    seg_tree(int sz) {
        N = 1;
        while (N < sz) N <<= 1;
        cnt.assign(N<<1, 0);
        len.assign(N<<1, 0);
    }
    void add_range(int i, int j, int k) {
        add_range_util(1, 0, N-1, i, j, k);
    }
    int query() {
        return len[1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    edges.resize(N<<1);
    Ys.resize(N<<1);
    for (int i = 0; i < N; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        edges[i<<1]     = { true, x1, y1, y2 };
        edges[i<<1 | 1] = { false, x2, y1, y2 };
        Ys[i<<1]        = y1;
        Ys[i<<1 | 1]    = y2;
    }
    sort(edges.begin(), edges.end());
    sort(Ys.begin(), Ys.end());
    Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());

    seg_tree segt(Ys.size());
    int x_prev = 0;
    uint64_t L = 0ul, S = 0ul;
    for (const auto& edge : edges) {
        S += L * (edge.x - x_prev);
        x_prev = edge.x;
        segt.add_range(
            y_to_idx(edge.y1), y_to_idx(edge.y2)-1,
            edge.is_left ? 1 : -1);
        L = segt.query();
    }

    cout << S << '\n';
    return 0;
}
