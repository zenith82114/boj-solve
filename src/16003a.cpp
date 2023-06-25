/*
 * Q16003a - Chordal graph; lexicographic BFS
 * Date: 2023.6.25
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100'001];
set<int> sadj[100'001];

struct vset {
    list<int> ls;
    int upd;
};

list<vset> vss;
list<vset>::iterator itr_vs[100'001];
list<int>::iterator itr_ls[100'001];
bitset<100'001> visited;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N, M; cin >> N >> M;
    while (M--) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
        sadj[x].emplace(y);
        sadj[y].emplace(x);
    }

    vss.emplace_back();
    auto& vs = vss.front();
    vs.upd = 0;
    for (int x = 1; x <= N; ++x) {
        vs.ls.emplace_back(x);
        itr_vs[x] = vss.begin();
    }
    auto itr = vs.ls.begin();
    for (int x = 1; x <= N; ++x) { itr_ls[x] = itr; ++itr; }

    vector<int> ord;

    while (!vss.empty()) {
        auto& vs = vss.front();
        if (vs.ls.empty()) {
            vss.pop_front(); continue;
        }
        int x = vs.ls.front(); vs.ls.pop_front();
        ord.emplace_back(x);
        visited.set(x);

        for (int y : adj[x]) if (!visited[y]) {
            auto& itr = itr_vs[y];
            if (itr->upd != x) {
                auto pitr = vss.emplace(itr);
                pitr->upd = 0;
                itr->upd = x;
            }
            itr->ls.erase(itr_ls[y]);
            --itr;
            itr->ls.emplace_back(y);
            itr_vs[y] = itr;
            itr_ls[y] = --(itr->ls.end());
        }
    }

    vector<int> iord(N+1);
    for (int i = 0; i < N; ++i) iord[ord[i]] = i;

    for (int x = 1; x <= N; ++x) {
        int t = -1;
        for (int y : adj[x]) if (iord[y] < iord[x]) t = max(t, iord[y]);
        if (t == -1) continue;
        int px = ord[t];
        const auto& s = sadj[px];
        for (int y : adj[x]) {
            if (y != px && iord[y] < iord[x] && s.find(y) == s.end()) {
                cout << 0; return 0;
            }
        }
    }
    cout << 1 << '\n';
    for (int i = N-1; ~i; --i) cout << ord[i] << ' ';

    return 0;
}
