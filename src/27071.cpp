/*
 * Q27071 - Kruskal's alg. + Kirchhoff's theorem
 * Date: 2024.2.15
 */

#include<bits/stdc++.h>
using namespace std;

struct mint {
    constexpr static int MOD = 998244353;
    int val;
    mint(): val(0) {}
    mint(int v): val(v) {
        if (val >= MOD) val %= MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(-val); }
    mint pow(int e) const {
        mint y(1), x(*this);
        for (; e; e >>= 1) { if (e&1) { y *= x; } x *= x; }
        return y;
    }
    mint inv() const { return pow(MOD - 2); }

    bool operator==(const mint& x) const { return val == x.val; }
    bool operator!=(const mint& x) const { return val != x.val; }
    bool operator!() const { return !val; }
    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator-(const mint& x) const { return mint(*this) -= x; }
    mint& operator-=(const mint& x) {
        if ((val -= x.val) < 0) val += MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

class disjoint_sets {
    vector<int> ar;
public:
    disjoint_sets(int sz): ar(sz, -1) {}
    int find(int x) {
        return ar[x] < 0? x : (ar[x] = find(ar[x]));
    }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        ar[y] = x; return true;
    }
};

vector<int> adj[404];
bitset<404> vis;
mint mat[404][404];

void dfs(int x, vector<int>& cc) {
    vis.set(x);
    cc.emplace_back(x);
    for (int y : adj[x]) if (!vis[y]) dfs(y, cc);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    struct edg_ { int x, y, w; };
    vector<edg_> edg(m);
    for (auto& [x, y, w] : edg) cin >> x >> y >> w;
    sort(edg.begin(), edg.end(), [] (const edg_& a, const edg_& b) {
        return a.w < b.w;
    });

    disjoint_sets dsu(n+1);
    mint ans(1);

    for (int l = 0, r = 0; l < m; l = r) {
        while (r < m && edg[l].w == edg[r].w) ++r;

        vector<int> vtx;

        for (int id = l; id < r; ++id) {
            auto& [x, y, w] = edg[id];
            x = dsu.find(x); y = dsu.find(y);
            adj[x].clear(); adj[y].clear();
            vis.reset(x); vis.reset(y);
            mat[x][x] = 0; mat[y][y] = 0;
            mat[x][y] = 0; mat[y][x] = 0;
        }
        for (int id = l; id < r; ++id) {
            const auto& [x, y, w] = edg[id];
            if (x == y) continue;
            vtx.emplace_back(x); vtx.emplace_back(y);
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
            mat[x][x] += 1; mat[y][y] += 1;
            mat[x][y] -= 1; mat[y][x] -= 1;
        }
        sort(vtx.begin(), vtx.end());
        vtx.erase(unique(vtx.begin(), vtx.end()), vtx.end());

        for (int x : vtx) if (!vis[x]) {
            vector<int> cc; dfs(x, cc);
            int dim = cc.size() - 1;

            for (int i = 0; i < dim; ++i) {
                int xi = cc[i];
                for (int j = i+1; j < dim; ++j) {
                    int xj = cc[j];
                    mint f = (-mat[xj][xi])/mat[xi][xi];
                    for (int k = i; k < dim; ++k) {
                        int xk = cc[k];
                        mat[xj][xk] += f * mat[xi][xk];
                    }
                }
            }
            for (int i = 0; i < dim; ++i) ans *= mat[cc[i]][cc[i]];
        }

        int cnt = 0;
        for (int id = l; id < r; ++id) {
            const auto& [x, y, w] = edg[id];
            if (dsu.unite(x, y)) ++cnt;
        }
        for (int i = 2; i <= cnt; ++i) ans *= i;
    }

    cout << ans;
    return 0;
}
