/*
 * Q15678 - DP + subarray minimum w/ deque
 * Date: 2022.1.13
 */

#include<iostream>
#include<deque>
using namespace std;

struct Element {
    int64_t val; int idx;
    Element(int64_t v, int i): val(v), idx(i) {}
};
deque<Element> dq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, D; cin >> N >> D;
    int64_t a; cin >> a;
    dq.emplace_back(a, 0);
    int64_t M = a;
    for (int n = 1; n < N; ++n) {
        cin >> a;
        a = max(a, a + dq.front().val);
        while (!dq.empty() && dq.back().val <= a)
            dq.pop_back();
        if (!dq.empty() && dq.front().idx + D == n)
            dq.pop_front();
        dq.emplace_back(a, n);
        M = max(M, dq.front().val);
    }

    cout << M << '\n';
    return 0;
}
