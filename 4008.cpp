/*
 * Q4008 - Convex hull trick
 * Date: 2022.2.15
 */

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll y0, m;
    Line(ll y0, ll m) : y0(y0), m(m) {};
};
inline ll cx(const Line& a, const Line& b) {
    return (b.y0 - a.y0)/(a.m - b.m);
}
deque<Line> hl;
int sz;
vector<ll> S;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll a, b, c, dp;
    int N;

    cin >> N >> a >> b >> c;
    S.resize(N);
    cin >> S[0];
    for (int n=1; n<N; n++) {
        cin >> S[n];
        S[n] += S[n-1];
    }

    dp = a*S[0]*S[0] + b*S[0] + c;
    sz = 1, hl.emplace_back(0, 0);
    for (int n=0; n+1<N; n++) {
        Line line(dp + a*S[n]*S[n] - b*S[n], -2*a*S[n]);

        if (sz && hl[sz-1].m == line.m && hl[sz-1].y0 <= line.y0)
            sz--, hl.pop_back();
        while (sz>1 && cx(line, hl[sz-1]) <= cx(hl[sz-1], hl[sz-2]))
            sz--, hl.pop_back();
        sz++, hl.emplace_back(line);

        while (sz>1 && cx(hl[1], hl[0]) < S[n+1])
            sz--, hl.pop_front();
        dp = hl[0].y0 + hl[0].m*S[n+1] + a*S[n+1]*S[n+1] + b*S[n+1] + c;
    }

    cout << dp << '\n';
    return 0;
}
