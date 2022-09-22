/*
 * Q6549a - Monotone stack
 * Date: 2022.3.13, 2022.9.22(revised)
 */

#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    while (N) {
        int h, nb, hb;
        ulong M = 0;
        stack<pii> stk;
        for (int n = 0; n < N; ++n) {
            int h; cin >> h;
            int nb = n;
            while (!stk.empty() && h < stk.top().second) {
                nb = stk.top().first;
                int hb = stk.top().second;
                M = max(M, 1ul * hb * (n - nb));
                stk.pop();
            }
            stk.emplace(nb, h);
        }
        while (!stk.empty()) {
            int nb = stk.top().first;
            int hb = stk.top().second;
            M = max(M, 1ul * hb * (N - nb));
            stk.pop();
        }
        cout << M << '\n';
        cin >> N;
    }

    return 0;
}
