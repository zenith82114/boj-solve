/*
 * Q15678 - DP + subarray minimum w/ deque
 * Date: 2022.1.13
 */

#include<iostream>
#include<deque>
using namespace std;

struct Element { int64_t val; int idx; };
deque<Element> dq;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, D;
    int64_t a, M;

    cin >> N >> D >> a;
    dq.push_back({a, 0});
    M = a;
    for (int n = 1; n < N; n++) {
        cin >> a;
        a = max(a, a + dq.front().val);
        while (!dq.empty() && dq.back().val <= a)
            dq.pop_back();
        if (!dq.empty() && dq.front().idx + D == n)
            dq.pop_front();
        dq.push_back({a, n});
        M = max(M, dq.front().val);
    }

    cout << M << '\n';
    return 0;
}
