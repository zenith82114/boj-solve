/*
 * Q16357 - Sweeping + Lazy-prop segment tree
 * Date: 2022.2.11
 */

#include<bits/stdc++.h>
using namespace std;

class seg_tree {
    int N;
    vector<int> A, lazy;

    int lc(int n) { return n<<1; }
    int rc(int n) { return n<<1 | 1; }
    void add_util(int n, int l, int r, int i, int j, int x) {
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
            add_util(lc(n), l, m, i, j, x);
            add_util(rc(n), m+1, r, i, j, x);
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
    int query_util(int n, int l, int r, int i, int j) {
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
            return max(query_util(lc(n), l, m, i, j),
            query_util(rc(n), m+1, r, i, j));
        return A[n];
    }
public:
    void init(int _N) {
        N = _N;
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.assign(sz<<1, 0);
        lazy.assign(A.size(), 0);
    }
    void add(int i, int j, int x) {
        add_util(1, 0, N-1, i, j, x);
    }
    int query(int i, int j) {
        return query_util(1, 0, N-1, i, j);
    }
} segt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    struct Ypoint {
        int y, id;
        Ypoint(int y, int id) : y(y), id(id) {}
        bool operator<(const Ypoint& rhs) {
            return y < rhs.y;
        }
    };
    vector<Ypoint> Yv;

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int yh, yl;
        cin >> yh >> yh >> yl >> yl;
        Yv.emplace_back(yl, i<<1);
        Yv.emplace_back(yh, i<<1|1);
    }
    sort(Yv.begin(), Yv.end());

    vector<int> ylv(N<<1);
    vector<vector<int>> yl_to_yh(N<<1);
    vector<int> ends_at(N<<1|1, 0);
    segt.init(N<<1);
    int ny = -1;
    int py = INT_MIN;

    for (auto& Y : Yv) {
        if (py < Y.y) {
            ny++;
            py = Y.y;
        }
        if (Y.id & 1) {
            int yl = ylv[Y.id>>1];
            yl_to_yh[yl].emplace_back(ny);
            ends_at[ny+1]++;
            segt.add(yl, ny, 1);
        }
        else
            ylv[Y.id>>1] = ny;
    }

    int res = 0, tmp = 0;
    for (int yl = 0; yl < ny; ++yl) {
        for (int& yh : yl_to_yh[yl]) {
            tmp++;
            segt.add(yl, yh, -1);
        }
        tmp -= ends_at[yl];
        res = max(res, tmp + segt.query(yl, ny));
    }

    cout << res << '\n';
    return 0;
}
