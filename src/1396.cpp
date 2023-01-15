/*
 * Q1396 - Parallel binary search
 * Date: 2023.1.15
 */

#include<bits/stdc++.h>
using namespace std;

class UnionFind {
    vector<int> arr;
    int find(int x) {
        if (arr[x] < 0) return x;
        return arr[x] = find(arr[x]);
    }
public:
    UnionFind(int sz): arr(sz, -1) {}
    void reset() {
        fill(arr.begin(), arr.end(), -1);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (arr[x] < arr[y]) swap(x, y);
            arr[y] += arr[x];
            arr[x] = y;
        }
    }
    bool united(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return -arr[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;

    struct edge { int a, b, c; };
    vector<edge> edges(M);
    for (auto& [a, b, c] : edges) cin >> a >> b >> c;
    sort(edges.begin(), edges.end(), [] (const edge& e1, const edge& e2) {
        return e1.c < e2.c;
    });

    int Q; cin >> Q;
    constexpr int MAXC = 1'000'000;

    struct query { int x, y, lo, hi; };
    vector<query> queries(Q);
    for (auto& [x, y, lo, hi] : queries) {
        cin >> x >> y;
        lo = 1;
        hi = MAXC;
    }

    vector<vector<int>> ls(MAXC+1);
    UnionFind uf(N+1);

    for (int iter = 1; iter < MAXC; iter <<= 1) {
        for (auto& l : ls) l.clear();
        for (int i = 0; i < Q; ++i) {
            const auto& [x, y, lo, hi] = queries[i];
            if (lo != hi)
                ls[(lo + hi)>>1].emplace_back(i);
        }

        auto e = edges.begin();
        uf.reset();
        for (int c = 1; c <= MAXC; ++c) {
            if (e != edges.end() && e->c == c) {
                uf.unite(e->a, e->b);
                ++e;
            }

            for (const int& i : ls[c]) {
                auto& [x, y, lo, hi] = queries[i];
                if (uf.united(x, y))
                    hi = c;
                else
                    lo = c+1;
            }
        }
    }

    vector<int> answers(Q);

    for (auto& l : ls) l.clear();
    for (int i = 0; i < Q; ++i) {
        const auto& [x, y, lo, hi] = queries[i];
        ls[lo].emplace_back(i);
    }

    auto e = edges.begin();
    uf.reset();
    for (int c = 1; c <= MAXC; ++c) {
        if (e != edges.end() && e->c == c) {
            uf.unite(e->a, e->b);
            ++e;
        }

        for (const int& i : ls[c]) {
            auto& [x, y, lo, hi] = queries[i];
            answers[i] = uf.united(x, y)? uf.size(x) : -1;
        }
    }

    for (int i = 0; i < Q; ++i) {
        if (answers[i] == -1) cout << "-1\n";
        else cout << queries[i].lo << ' ' << answers[i] << '\n';
    }
    return 0;
}
