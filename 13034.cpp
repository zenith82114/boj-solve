/*
 * Q13034 - Sprague-Grundy theorem
 * Date: 2022.9.28
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> g;

int G(int n) {
    int &ret = g[n];
    if (g[n] != -1)
        return ret;

    set<int> s;
    s.emplace(G(n-2));
    for (int i = 1; 2*i <= n-2; ++i)
        s.emplace(G(i) ^ G(n-2-i));
    ret = 0;
    while (s.find(ret) != s.end()) ++ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    g.resize(N+1, -1);
    g[0] = 0;
    g[1] = 0;
    cout << (G(N) > 0? 1 : 2) << '\n';

    return 0;
}
