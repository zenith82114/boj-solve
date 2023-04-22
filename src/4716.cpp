/*
 * Q4716 - Greedy
 * Date: 2023.4.22
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, A, B; cin >> N >> A >> B;
    while (N | A | B) {
        vector<int> K(N);
        vector<tuple<int, int, int, bool> > v;

        for (int i = 0; i < N; ++i) {
            int a, b; cin >> K[i] >> a >> b;
            int w = - abs(a - b);
            v.emplace_back(w, a, i, true);
            v.emplace_back(w, b, i, false);
        }
        sort(v.begin(), v.end());

        int ans = 0;
        for (auto& [w, d, i, q] : v) {
            int& M = q? A : B;
            int x = min(M, K[i]);
            M -= x;
            K[i] -= x;
            ans += x * d;
        }
        cout << ans << '\n';
        cin >> N >> A >> B;
    }

    return 0;
}
