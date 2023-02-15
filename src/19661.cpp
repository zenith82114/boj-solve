/*
 * Q19661 - DP + Segment tree
 * Date: 2023.2.15
 */

#include<bits/stdc++.h>
using namespace std;

class SegTree {
    int N;
    vector<int> ar;
public:
    SegTree(int sz) {
        for (N = 1; N < sz; N <<= 1);
        ar.resize(N<<1);
    }
    void update(int i, int x) {
        if (ar[i |= N] >= x) return;
        for (ar[i] = x; i > 1; i >>= 1)
            ar[i>>1] = max(ar[i], ar[i^1]);
    }
    int query(int j) {
        int ans = 0;
        int i = N;
        for (j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) ans = max(ans, ar[i++]);
            if (~j&1) ans = max(ans, ar[j--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    struct point { int x, y; point(int x, int y): x(x), y(y) {} };
    vector<point> pts;
    vector<int> xs { 0 };

    int N, M; cin >> N >> M;
    vector<int> T(M);
    for (int& t : T) cin >> t;
    for (const int& t : T) {
        int a; cin >> a;
        pts.emplace_back(a + t, t - a);
        xs.emplace_back(a + t);
    }

    SegTree segt(M+1);
    sort(pts.begin(), pts.end(), [] (const point& p1, const point& p2) {
        return p1.y != p2.y? p1.y > p2.y : p1.x > p2.x;
    });
    sort(xs.begin(), xs.end());

    int ans = 0;
    for (const auto& [x, y] : pts) {
        int j = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        int r = segt.query(j-1);
        segt.update(j, r+1);
        ans = max(ans, r+1);
    }

    cout << ans;
    return 0;
}
