/*
 * Q1624 - Greedy
 * Date: 2023.3.5
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N);
    for (int& a : A) cin >> a;

    vector<int> sA(A);
    sort(sA.begin(), sA.end());
    sA.erase(unique(sA.begin(), sA.end()), sA.end());
    auto rank = [&sA] (int x) {
        return lower_bound(sA.begin(), sA.end(), x) - sA.begin();
    };

    int M = sA.size();
    vector<pair<int, int>> idx(M, {N, -1});
    for (int i = 0; i < N; ++i) {
        auto& [l, r] = idx[rank(A[i])];
        l = min(l, i);
        r = max(r, i);
    }

    int b = INT_MAX;
    int ans = 1;
    bool down = true;
    for (int i = 0; i < M; ++i) {
        auto& [l, r] = idx[i];
        if (down) {
            if (b < r) {
                down = false;
                b = r;
            }
            else b = l;
        }
        else {
            if (b < l) b = r;
            else {
                ans++;
                down = true;
                b = l;
            }
        }
    }

    cout << ans;
    return 0;
}
