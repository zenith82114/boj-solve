/*
 * Q6549a - Monotonic stack
 * Date: 2022.3.13
 */

#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

vector<pii> stk;
int sz;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    while (N) {
        int h, nb, hb;
        ulong M = 0;
        stk.clear(); sz = 0;
        for (int n = 0; n < N; ++n) {
            cin >> h;
            nb = n;
            while (sz && h < stk.back().second) {
                tie(nb, hb) = stk.back();
                stk.pop_back(); sz--;
                M = max(M, (ulong)hb * (n - nb));
            }
            stk.emplace_back(nb, h); sz++;
        }
        while (sz--) {
            tie(nb, hb) = stk.back();
            stk.pop_back();
            M = max(M, (ulong)hb * (N - nb));
        }
        cout << M << '\n';
        cin >> N;
    }

    return 0;
}
