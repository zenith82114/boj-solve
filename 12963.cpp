/*
 * Q12963 - Greedy + Union-find
 * Date: 2022.11.13
 */

#include<bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;

class union_find {
    vector<int> par, rnk;
public:
    union_find(int sz): par(sz, -1), rnk(sz, 1) {}
    int find(int x) {
        if (par[x] == -1) return x;
        return find(par[x]);
    }
    bool query(int x, int y) {
        return find(x) != find(y);
    }
    int unite(int x, int y) {
        x = find(x), y = find(y);
        if (rnk[x] < rnk[y]) {
            par[x] = y;
            return x;
        }
        else {
            par[y] = x;
            if (rnk[x] == rnk[y]) ++rnk[x];
            return y;
        }
    }
    void rollback(int log) { par[log] = -1; }
};

inline int mul_mod(int a, int b, int p) {
    return (1ll * a * b) % p;
}

inline int pow_mod(int a, int x, int p) {
    int y = 1;
    while (x) {
        if (x&1) y = mul_mod(y, a, p);
        x >>= 1; a = mul_mod(a, a, p);
    }
    return y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<pair<int, int>> E(M);
    for (int i = M-1; ~i; --i) {
        auto& e = E[i]; cin >> e.first >> e.second;
    }

    union_find uf(N);

    constexpr int MOD = 1'000'000'007;
    const int inv_3 = pow_mod(3, MOD-2, MOD);

    int w = pow_mod(3, M, MOD);
    int ans = 0;
    for (const auto& e : E) {
        int x, y; tie(x, y) = e;
        w = mul_mod(w, inv_3, MOD);

        if (uf.query(x, y)) {
            int log = uf.unite(x, y);
            if (!uf.query(0, N-1)) {
                ans = (ans + w) % MOD;
                uf.rollback(log);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
