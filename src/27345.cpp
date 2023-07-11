/*
 * Q27345 - Slope trick
 * Date: 2023.7.11
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    using i64 = int64_t;

    priority_queue<i64> pq;
    i64 y0 = 0;
    i64 x = 0;

    int N; cin >> N;
    while (N--) {
        int a, b; cin >> a >> b;
        x += a - b;
        y0 += abs(x);
        if (x < 0) { pq.emplace(0); }
        else { pq.emplace(x); pq.emplace(x); }
        pq.pop();
    }
    while (!pq.empty()) {
        y0 -= min(pq.top(), x);
        pq.pop();
    }
    cout << y0;
    return 0;
}
