/*
 * Q16357 - Sweeping + Lazy-prop segment tree
 * Date: 2022.2.11
 */

#include<bits/stdc++.h>
using namespace std;

class SegTree {
    int N;
    vector<int> A, lazy;
    constexpr int ceilPow2(int n) {
        if (n & (n-1)) {
            for (int i=1; i<32; i<<=1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }
    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1 | 1; }
    void addUtil(int n, int l, int r, int i, int j, int x) {
        int m = (l+r)/2;
        if (lazy[n]) {
            A[n] += lazy[n];
            if (l != r) {
                lazy[lc(n)] += lazy[n];
                lazy[rc(n)] += lazy[n];
            }
            lazy[n] = 0;
        }
        if (l > j || r < i)
            return;
        if (l < i || r > j) {
            addUtil(lc(n), l, m, i, j, x);
            addUtil(rc(n), m+1, r, i, j, x);
            A[n] = max(A[lc(n)], A[rc(n)]);
        }
        else {
            A[n] += x;
            if (l != r) {
                lazy[lc(n)] += x;
                lazy[rc(n)] += x;
            }
        }
    }
    int queryUtil(int n, int l, int r, int i, int j) {
        int m = (l+r)/2;
        if (lazy[n]) {
            A[n] += lazy[n];
            if (l != r) {
                lazy[lc(n)] += lazy[n];
                lazy[rc(n)] += lazy[n];
            }
            lazy[n] = 0;
        }
        if (l > j || r < i)
            return 0;
        if (l < i || r > j)
            return max(queryUtil(lc(n), l, m, i, j),
            queryUtil(rc(n), m+1, r, i, j));
        return A[n];
    }
public:
    void init(int _N) {
        N = _N;
        A.assign(ceilPow2(N)<<1, 0);
        lazy.assign(A.size(), 0);
    }
    void add(int i, int j, int x) {
        addUtil(1, 0, N-1, i, j, x);
    }
    int query(int i, int j) {
        return queryUtil(1, 0, N-1, i, j);
    }
} segt;

struct Ypoint {
    int y, id;
    Ypoint(int y, int id) : y(y), id(id) {}
    bool operator<(const Ypoint& rhs) {
        return y < rhs.y;
    }
};
vector<Ypoint> Yv;
vector<vector<int>> yl2yh;
vector<int> ylv, endsAt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, yl, yh, py, ny;
    int res, tmp;

    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> yh >> yh >> yl >> yl;
        Yv.emplace_back(yl, i<<1);
        Yv.emplace_back(yh, i<<1|1);
    }
    sort(Yv.begin(), Yv.end());

    ylv.resize(N<<1);
    yl2yh.resize(N<<1);
    endsAt.assign(N<<1|1, 0);
    segt.init(N<<1);
    ny = -1;
    py = INT_MIN;
    for (auto& Y : Yv) {
        if (py < Y.y) {
            ny++;
            py = Y.y;
        }
        if (Y.id & 1) {
            yl = ylv[Y.id>>1];
            yl2yh[yl].emplace_back(ny);
            endsAt[ny+1]++;
            segt.add(yl, ny, 1);
        }
        else
            ylv[Y.id>>1] = ny;
    }

    res = tmp = 0;
    for (yl=0; yl<ny; yl++) {
        for (int& yh : yl2yh[yl]) {
            tmp++;
            segt.add(yl, yh, -1);
        }
        tmp -= endsAt[yl];
        res = max(res, tmp + segt.query(yl, ny));
    }

    cout << res << '\n';
    return 0;
}
