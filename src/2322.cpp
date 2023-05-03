/*
 * Q2322 - Permutation cycle decomposition
 * Date: 2023.5.3
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    using i64 = int64_t;

    int N; cin >> N;
    vector<pair<i64, int> > A; A.reserve(N);
    i64 ans = 0;
    for (int i = 0; i < N; ++i) {
        i64 a; cin >> a;
        A.emplace_back(a, i);
        ans += a;
    }
    sort(A.begin(), A.end());

    const i64 a0 = A[0].first;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; ++i) if (!visited[i]) {
        const i64 a = A[i].first;
        int len = 0;
        for (int j = i; !visited[j]; j = A[j].second) {
            visited[j] = true;
            ++len;
        }
        ans += min(a * (len - 2), a + a0 * (len + 1));
    }

    cout << ans;
    return 0;
}
