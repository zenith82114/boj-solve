/*
 * Q22360 - Smaller to Larger
 * Date: 2023.3.14
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> tree[200'000];
string S;
map<pair<int, int>, int> mps[200'000];

i64 dfs(int pu, int u, int x_pu, int y_pu) {
    int x_u = x_pu + (S[u] == 'U'? 1 : S[u] == 'P'? -1 : 0);
    int y_u = y_pu + (S[u] == 'C'? -1 : 1);
    i64 ret = 0;

    auto& mp_u = mps[u];
    mp_u.emplace(make_pair(x_u, y_u), 1);

    for (int& v : tree[u]) if (v != pu) {
        ret += dfs(u, v, x_u, y_u);
        auto& mp_v = mps[v];
        if (mp_u.size() < mp_v.size()) swap(mp_u, mp_v);

        for (auto& [k1, n1] : mp_v) {
            auto& [x1, y1] = k1;
            auto k2 = make_pair(x_pu + x_u - x1, y_pu + y_u - y1);
            if (mp_u.count(k2))
                ret += (i64)n1 * mp_u[k2];
        }

        for (auto& [k, n] : mp_v) mp_u[k] += n;
        mp_v.clear();
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    cin >> S;
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    cout << dfs(-1, 0, 0, 0);
    return 0;
}
