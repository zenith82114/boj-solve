/*
 * Q2569 - Cycle decomposition
 * Date: 2022.10.31
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> A(N);
    int M = 0;
    int ans = 0;
    for (int& a : A) {
        cin >> a;
        M = max(M, a);
        ans += a;
    }

    vector<int> enc(M+1), dec(A);
    sort(dec.begin(), dec.end());
    for (int i = 0; i < N; ++i) enc[dec[i]] = i;

    vector<bool> visited(N, false);
    vector<pair<int, int>> cycles;
    for (int i = 0; i < N; ++i) if (!visited[i]) {
        int len = 0;
        for (int j = i; !visited[j]; j = enc[A[j]]) {
            visited[j] = true;
            ++len;
        }
        cycles.emplace_back(dec[i], len);
    }

    const int& a0 = cycles[0].first;
    for (const auto& [a, k] : cycles) {
        ans += min(a * (k-2), a + a0 * (k+1));
    }
    cout << ans << endl;
    return 0;
}
