/*
 * Q17131 - Sweep + segment tree
 * Date: 2022.1.4
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef pair<int64_t, int64_t> pair_t;

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
    pair_t removeUtil(int k, int n, int l, int r) {
        int m;
        pair_t p;
        A[n]--;
        if (l != r) {
            m = (l + r) / 2;
            if (k > m) {
                p = removeUtil(k, rChild(n), m + 1, r);
                p.first += A[lChild(n)];
            }
            else {
                p = removeUtil(k, lChild(n), l, m);
                p.second += A[rChild(n)];
            }
            return p;
        }
        else return {0, 0};
    }
public:
    SegTree(int _N) {
        N = _N;
        A.resize(2 * ceil_pow2(N), 0);
    }
    void insert(int k) {
        int n = 1, l = 0, r = N - 1;
        int m;
        A[1]++;
        while (l < r) {
            m = (l + r) / 2;
            if (k > m) {
                l = m + 1;
                n = rChild(n);
            }
            else {
                r = m;
                n = lChild(n);
            }
            A[n]++;
        }
    }
    // remove k and return {# elements < k, # elements > k}
    pair_t remove(int k) {
        return removeUtil(k, 1, 0, N - 1);
    }
};

// coordinate compression
vector<int> x_idx;
int xToIdx(int x) {
    auto p = lower_bound(x_idx.begin(), x_idx.end(), x);
    return distance(x_idx.begin(), p);
}

struct Point { int x, y; };
vector<Point> points;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N;
    pair_t res;
    int64_t cnt = 0;

    cin >> N;
    points.resize(N);
    for (int i = 0; i < N; i++)
        cin >> points[i].x >> points[i].y;

    sort(points.begin(), points.end(),
        [](const Point& p1, const Point& p2){
            return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
        }
    );

    x_idx.resize(N);
    for (int i = 0; i < N; i++)
        x_idx[i] = points[i].x;
    sort(x_idx.begin(), x_idx.end());

    SegTree segt(N);
    for (auto p : points)
        segt.insert(xToIdx(p.x));

    // use two helper pointers to uncount points
    // with x >= p->x and y == p->y
    for (auto p = points.begin(), q = points.begin(), r = points.begin(),
    end = points.end(); p != end; p++) {
        while (q != end && p->x == q->x && p->y == q->y)
            q++;
        while (r != end && p->y == r->y)
            r++;
        res = segt.remove(xToIdx(p->x));
        cnt += res.first * (res.second - distance(q, r));
        cnt %= 1000000007;
    }

    cout << cnt << '\n';
    return 0;
}
