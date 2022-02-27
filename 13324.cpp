/*
 * Q13324 - Slope trick
 * Date: 2022.2.25
 * 
 * The variable M (commented) gives the minimized deviation. (Q13323)
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    priority_queue<int> pq;
    vector<int> T;
    int N, A;
    // ulong M = 0;

    cin >> N >> A;
    pq.emplace(A);
    T.resize(N), T[0] = A;
    for (int n=1; n<N; n++) {
        cin >> A;
        A -= n;
        if (A < pq.top()) {
            pq.emplace(A);
            // M += pq.top() - A;
            pq.pop();
        }
        pq.emplace(A);
        T[n] = pq.top();
    }

    // cout << M << '\n';
    for (int n=N-2; ~n; n--)
        T[n] = min(T[n], T[n+1]);
    for (int n=0; n<N; n++)
        cout << T[n] + n << '\n';
    return 0;
}
