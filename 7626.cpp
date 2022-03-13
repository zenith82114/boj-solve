/*
 * Q7626 - Union area of rectangles using sweep line + segment tree
 * Date: 2022.1.6, 2022.3.13(revised)
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct Edge {
    bool isLeftEdge;
    int x;
    int y1, y2;
    bool operator<(const Edge &e) {
        return x < e.x;
    }
};
vector<Edge> edges;

// coordinate compression
vector<int> Ys;
int yCoordToIndex(int y) {
    return distance(Ys.begin(), lower_bound(Ys.begin(), Ys.end(), y));
}
int yIndexToCoord(int i) {
    return Ys[i];
}

class SegTree {
    int N;
    vector<int> cnt, len;
    constexpr int ceil_pow2(int n) {
        if (n & (n - 1)) {
            for (int i = 1; i < 32; i <<= 1)
                n |= (n >> i);
            return n + 1;
        }
        return n;
    }
    constexpr int lChild(int n) { return n << 1; }
    constexpr int rChild(int n) { return n << 1 | 1; }
    void addRangeUtil(int n, int l, int r, int i, int j, int k) {
        int m = (l + r) >> 1;
        if (l > j || r < i)
            return;
        if (l < i || r > j) {
            addRangeUtil(lChild(n), l, m, i, j, k);
            addRangeUtil(rChild(n), m+1, r, i, j, k);
        }
        else cnt[n] += k;
        if (cnt[n])
            len[n] = yIndexToCoord(r+1) - yIndexToCoord(l);
        else if (l != r)
            len[n] = len[lChild(n)] + len[rChild(n)];
        else
            len[n] = 0;
    }
public:
    SegTree(int _N) {
        int size = ceil_pow2(_N) << 1;
        N = _N;
        cnt.assign(size, 0);
        len.assign(size, 0);
    }
    void addRange(int i, int j, int k) {
        addRangeUtil(1, 0, N-1, i, j, k);
    }
    int query() {
        return len[1];
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, x1, x2, y1, y2, x_prev;
    ulong L, S;

    cin >> N;
    edges.resize(N<<1);
    Ys.resize(N<<1);
    for (int i = 0; i < N; i++) {
        cin >> x1 >> x2 >> y1 >> y2;
        edges[i<<1]     = { true, x1, y1, y2 };
        edges[i<<1 | 1] = { false, x2, y1, y2 };
        Ys[i<<1]        = y1;
        Ys[i<<1 | 1]    = y2;
    }
    sort(edges.begin(), edges.end());
    sort(Ys.begin(), Ys.end());
    Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());

    SegTree segt(Ys.size());
    x_prev = 0;
    L = S = 0;
    for (auto& edge : edges) {
        S += L * (edge.x - x_prev);
        x_prev = edge.x;
        segt.addRange(
            yCoordToIndex(edge.y1), yCoordToIndex(edge.y2)-1,
            edge.isLeftEdge ? 1 : -1);
        L = segt.query();
    }

    cout << S << '\n';
    return 0;
}
