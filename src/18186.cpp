/*
 * Q18186 - Greedy
 * Date: 2023.7.14
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    int N; i64 B, C; cin >> N >> B >> C;
    i64 ans = 0;
    if (B <= C) {
        while (N--) { int x; cin >> x; ans += B*x; }
    } else {
        int b2 = 0, b1 = 0;
        int c1 = 0;
        for (int i = 0; i < N; ++i) {
            int a; cin >> a;
            int x = min({b2, c1, a});
            x += min(b1, a - x);
            ans += B*(a - x) + C*x;
            b2 = b1; b1 = a - x;
            c1 = x;
        }
    }
    cout << ans;
    return 0;
}
