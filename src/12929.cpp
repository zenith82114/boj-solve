/*
 * Q12929 - Greedy + Binary search
 * Date: 2023.1.27
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    using i64 = int64_t;

    int N, K; cin >> N >> K;
    int M; cin >> M;

    vector<i64> X(M), T(M);
    for (i64& x : X) cin >> x;
    for (i64& t : T) cin >> t;
    if (!X.empty() && X.front() == 1ll) T.front() = 0ll;
    else {
        X.insert(X.begin(), 1ll);
        T.insert(T.begin(), 0ll);
        M++;
    }
    if (M < 2) {
        cout << (i64)K * (N-1);
        return 0;
    }

    for (int i = 1; i < M; ++i)
        T[i] = min(T[i], T[i-1] + K*(X[i] - X[i-1]));
    for (int i = M-2; i; --i)
        T[i] = min(T[i], T[i+1] - K*(X[i] - X[i+1]));

    i64 ans = 0ll;
    for (int i = 0; i+1 < M; ++i) {
        if (T[i] >= T[i+1] + K*(X[i+1] - X[i])) {
            ans = max(ans, T[i+1] + K*(X[i+1] - X[i]));
        }
        else if (T[i+1] >= T[i] + K*(X[i+1] - X[i])) {
            ans = max(ans, T[i] + K*(X[i+1] - X[i]));
        }
        else {
            i64 x = X[i];
            for (i64 d = X[i+1] - X[i]; d; d >>= 1) {
                while (x+d <= X[i+1] && T[i] + K*(x+d - X[i]) <= T[i+1] - K*(x+d - X[i+1]))
                    x += d;
            }
            ans = max(ans, T[i] + K*(x - X[i]));
            if (x < X[i+1]) ans = max(ans, T[i+1] - K*(x+1 - X[i+1]));
        }
    }

    ans = max(ans, T[M-1] + K*(N - X[M-1]));
    cout << ans;
    return 0;
}
