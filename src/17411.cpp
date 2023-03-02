/*
 * Q17411 - Segment tree
 * Date: 2023.3.2
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class SegTree {
    static const int MOD = 1e9 +7;
    int N;
    vector<ii> arr;
public:
    SegTree(int sz) {
        for (N = 1; N < sz; N <<= 1);
        arr.resize(N<<1);
    }
    ii query(int j) {
        ii ans = {0, 0};
        int i = N; j |= N;
        for (; i <= j; i >>= 1, j >>= 1) {
            if (i&1) {
                if (ans.first < arr[i].first)
                    ans = arr[i];
                else if (ans.first == arr[i].first)
                    ans.second = (ans.second + arr[i].second) % MOD;
                i++;
            }
            if (~j&1) {
                if (ans.first < arr[j].first)
                    ans = arr[j];
                else if (ans.first == arr[j].first)
                    ans.second = (ans.second + arr[j].second) % MOD;
                j--;
            }
        }
        return ans;
    }
    void update(int i, ii& x) {
        i |= N;
        if (arr[i].first < x.first)
            arr[i] = x;
        else if (arr[i].first == x.first)
            arr[i].second = (arr[i].second + x.second) % MOD;
        for (; i > 1; i >>= 1) {
            if (arr[i].first != arr[i^1].first)
                arr[i>>1] = max(arr[i], arr[i^1]);
            else
                arr[i>>1] = {arr[i].first, (arr[i].second + arr[i^1].second) % MOD};
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    A.emplace_back(INT_MIN);
    vector<int> sortA(A);
    sort(sortA.begin(), sortA.end());
    A.pop_back();

    SegTree segt(N+1);
    for (const int& a : A) {
        int i = lower_bound(sortA.begin(), sortA.end(), a) - sortA.begin();
        auto x = segt.query(i-1);
        if (!x.first) x.second = 1;
        x.first++;
        segt.update(i, x);
    }

    auto x = segt.query(N);
    cout << x.first << ' ' << x.second;
    return 0;
}
