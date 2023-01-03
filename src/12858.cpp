/*
 * Q12858 - Segment tree
 * Date: 2023.1.3
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;

class RUPQSegTree {
    int N;
    vector<i64> arr;
public:
    RUPQSegTree(vector<int>& data) {
        int n = data.size();
        for (N = 1; N < n; N <<= 1);
        arr.resize(N<<1, 0ll);
        copy(data.begin(), data.end(), arr.begin() + N);
    }
    void add(int i, int j, int x) {
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) arr[i++] += x;
            if (~j&1) arr[j--] += x;
        }
    }
    i64 query(int i) {
        i64 ans = arr[i |= N];
        for (; i > 1; i >>= 1) ans += arr[i>>1];
        return ans;
    }
};

class PURQSegTree {
    int N;
    vector<i64> arr;
public:
    PURQSegTree(vector<int>& data) {
        int n = data.size();
        for (N = 1; N < n; N <<= 1);
        arr.resize(N<<1, 0ll);
        copy(data.begin(), data.end(), arr.begin() + N);
        for (int i = N-1; i; --i)
            arr[i] = gcd(arr[i<<1], arr[i<<1|1]);
    }
    void add(int i, int x) {
        for (arr[i |= N] += x; i > 1; i >>= 1)
            arr[i>>1] = gcd(arr[i], arr[i^1]);
    }
    i64 query(int i, int j) {
        i64 ans = 0ll;
        for (i |= N, j |= N; i <= j; i >>= 1, j >>= 1) {
            if (i&1)  ans = gcd(ans, arr[i++]);
            if (~j&1) ans = gcd(ans, arr[j--]);
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N);
    for (int& a : A) cin >> a;
    RUPQSegTree segt1(A);
    adjacent_difference(A.begin(), A.end(), A.begin());
    PURQSegTree segt2(A);

    int Q; cin >> Q;
    while (Q--) {
        int t, i, j; cin >> t >> i >> j; --i; --j;
        if (t) {
            segt1.add(i, j, t);
            segt2.add(i, t);
            if (j+1 != N) segt2.add(j+1, -t);
        }
        else {
            i64 ans = segt1.query(i);
            if (i != j) ans = gcd(ans, segt2.query(i+1, j));
            cout << ans << '\n';
        }
    }
    return 0;
}
