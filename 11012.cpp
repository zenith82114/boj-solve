/*
 * Q11012 - 2D range query using sweep line + segment tree
 * Date: 2022.1.5
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

enum ItemType { LEFT_SIDE, POINT, RIGHT_SIDE };
struct Item {
    ItemType type;
    int x;
    int yb, yt;
    bool operator<(const Item &i) {
        return x != i.x ? x < i.x : type < i.type;
    }
};
vector<Item> items;

class SegTree {
    int N;
    vector<int> A;
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
        int m;
        if (i == l && j == r) {
            A[n] += k;
            return;
        }
        m = (l + r) / 2;
        if (j <= m)
            addRangeUtil(lChild(n), l, m, i, j, k);
        else if (i > m)
            addRangeUtil(rChild(n), m+1, r, i, j, k);
        else {
            addRangeUtil(lChild(n), l, m, i, m, k);
            addRangeUtil(rChild(n), m+1, r, m+1, j, k);
        }
    }
public:
    SegTree(int _N) {
        N = _N;
        A.resize(2 * ceil_pow2(N), 0);
    }
    void clear() { A.clear(); }
    void addRange(int i, int j, int k) {
        addRangeUtil(1, 0, N-1, i, j, k);
    }
    int query(int i) {
        int n = 1, l = 0, r = N-1, m;
        int q = A[1];
        while (l != r) {
            m = (l + r) / 2;
            if (i > m) {
                n = rChild(n);
                l = m+1;
            }
            else {
                n = lChild(n);
                r = m;
            }
            q += A[n];
        }
        return q;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    SegTree segt(100001);
    int TC, N, M;
    int xl, xr, yb, yt;
    int cnt;

    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        items.resize(N + 2*M);
        for (int i = 0; i < N; i++) {
            cin >> xl >> yb;
            items[i] = { POINT, xl, yb, };
        }
        for (int i = 0; i < M; i++) {
            cin >> xl >> xr >> yb >> yt;
            items[N + 2*i]     = { LEFT_SIDE, xl, yb, yt };
            items[N + 2*i + 1] = { RIGHT_SIDE, xr, yb, yt };
        }
        sort(items.begin(), items.end());

        segt.clear();
        cnt = 0;
        for (auto item : items) {
            switch (item.type) {
            case POINT:
                cnt += segt.query(item.yb);
                break;
            case LEFT_SIDE:
                segt.addRange(item.yb, item.yt, 1);
                break;
            case RIGHT_SIDE:
                segt.addRange(item.yb, item.yt, -1);
                break;
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
