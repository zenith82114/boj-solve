/*
 * Q17131 - Sweep + segment tree
 * Date: 2022.1.4
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef pair<int64_t, int64_t> pair_t;

class seg_tree {
    int N;
    vector<int> A;

    constexpr int lc(int n) { return n << 1; }
    constexpr int rc(int n) { return n << 1 | 1; }
    pair_t remove_util(int k, int n, int l, int r) {
        pair_t p;
        A[n]--;
        if (l != r) {
            int m = (l + r) / 2;
            if (k > m) {
                p = remove_util(k, rc(n), m + 1, r);
                p.first += A[lc(n)];
            }
            else {
                p = remove_util(k, lc(n), l, m);
                p.second += A[rc(n)];
            }
            return p;
        }
        else return pair_t(0, 0);
    }
public:
    seg_tree(int _N) {
        N = _N;
        int sz = 1;
        while (sz < N) sz <<= 1;
        A.resize(sz<<1, 0);
    }
    void insert(int k) {
        int n = 1, l = 0, r = N - 1;
        A[1]++;
        while (l < r) {
            int m = (l + r) / 2;
            if (k > m) {
                l = m + 1;
                n = rc(n);
            }
            else {
                r = m;
                n = lc(n);
            }
            A[n]++;
        }
    }
    pair_t remove(int k) {
        return remove_util(k, 1, 0, N - 1);
    }
};

// coordinate compression
vector<int> x_idx;
int x_to_idx(int x) {
    auto p = lower_bound(x_idx.begin(), x_idx.end(), x);
    return distance(x_idx.begin(), p);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    struct Point { int x, y; };
    vector<Point> points(N);
    for (auto& p : points) cin >> p.x >> p.y;
    sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
    });

    x_idx.resize(N);
    for (int i = 0; i < N; ++i)
        x_idx[i] = points[i].x;
    sort(x_idx.begin(), x_idx.end());

    seg_tree segt(N);
    for (auto& p : points)
        segt.insert(x_to_idx(p.x));

    int64_t cnt = 0ul;

    // use two helper pointers to uncount points
    // with x >= p->x and y == p->y
    for (auto p = points.begin(), q = points.begin(), r = points.begin(),
    end = points.end(); p != points.end(); ++p) {
        while (q != end && p->x == q->x && p->y == q->y)
            ++q;
        while (r != end && p->y == r->y)
            ++r;
        pair_t res = segt.remove(x_to_idx(p->x));
        cnt += res.first * (res.second - distance(q, r));
        cnt %= 1000000007;
    }

    cout << cnt << '\n';
    return 0;
}
