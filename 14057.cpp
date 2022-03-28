/*
 * Q14057 - Monotone stack + DP
 * Date: 2022.3.24
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> hei, hei_s, dp, opt;
struct Item {
    int val, idx;
    Item(int v, int i) : val(v), idx(i) {}
};
stack<Item> stk;

inline int htor(int h) {
    auto p = lower_bound(hei_s.begin(), hei_s.end(), h);
    return distance(hei_s.begin(), p);
}
inline int rtoh(int r) {
    return hei_s[r];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;
    hei.resize(N);
    for (int& h : hei)
        cin >> h;
    hei_s = hei;
    sort(hei_s.begin(), hei_s.end());
    hei_s.erase(unique(hei_s.begin(), hei_s.end()), hei_s.end());
    int M = hei_s.size();
    dp.resize(M, 0);
    opt.resize(M, -1);

    int r1 = 0, r2 = 0;
    int d;
    for (int n=0; n<N; ++n) {
        d = 2;
        while (!stk.empty() && stk.top().val <= hei[n]) {
            stk.pop();
            if (!stk.empty()) {
                auto p2 = stk.top();
                r2 = htor(p2.val);
                if (dp[r2] <= dp[r1] + 1 && p2.idx < opt[r1]) {
                    dp[r2] = dp[r1] + 1;
                    opt[r2] = p2.idx;
                }
                if (dp[r2] < d) {
                    dp[r2] = d;
                    opt[r2] = p2.idx;
                }
                ++d;
                r1 = r2;
            }
        }
        stk.emplace(hei[n], n);
        r1 = htor(hei[n]);
        if (dp[r1] <= 1) {
            dp[r1] = 1;
            opt[r1] = n;
        }
    }
    d = 2;
    while (!stk.empty()) {
        stk.pop();
        if (!stk.empty()) {
            auto p2 = stk.top();
            r2 = htor(p2.val);
            if (dp[r2] <= dp[r1] + 1 && p2.idx < opt[r1]) {
                dp[r2] = dp[r1] + 1;
                opt[r2] = p2.idx;
            }
            if (dp[r2] < d) {
                dp[r2] = d;
                opt[r2] = p2.idx;
            }
            ++d;
            r1 = r2;
        }
    }
    for (int i=1; i<M; ++i)
        dp[i] = max(dp[i], dp[i-1]);

    while (K--) {
        int h; cin >> h;
        int r = htor(h);
        if (r == M)
            cout << dp[M-1] << ' ';
        else if (rtoh(r) != h)
            cout << (r ? dp[r-1] : 0) << ' ';
        else cout << dp[r] << ' ';
    }
    cout << '\n';

    return 0;
}
