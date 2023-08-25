/*
 * Q18123 - Tree isomorphism
 * Date: 2023.8.25
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> adj[30];
int sz[30];

void get_sz(int px, int x) {
    sz[x] = 1;
    for (int y : adj[x]) if (y != px) {
        get_sz(x, y);
        sz[x] += sz[y];
    }
}

int get_cent(int px, int x, int k) {
    for (int y : adj[x]) if (y != px && sz[y] > k)
        return get_cent(x, y, k);
    return x;
}

string encode(int px, int x) {
    vector<string> v;
    for (int y : adj[x]) if (y != px) v.emplace_back(encode(x, y));
    sort(v.begin(), v.end());
    string tx("1");
    for (const auto& ty : v) tx.append(ty);
    tx.push_back('0');
    return tx;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    set<uint64_t> db;

    int n; cin >> n;
    while (n--) {
        int s; cin >> s;
        for (int x = 0; x < s; ++x) adj[x].clear();
        for (int i = 1; i < s; ++i) {
            int x, y; cin >> x >> y;
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        get_sz(-1, 0);
        int c1 = get_cent(-1, 0, s/2);
        string t1 = encode(-1, c1);

        get_sz(-1, c1);
        int c2 = -1;
        for (int y : adj[c1]) if (sz[y] >= s - s/2) {
            c2 = y; break;
        }

        if (c2 == -1) {
            db.emplace(stoull(t1, 0, 2));
        } else {
            string t2 = encode(-1, c2);
            db.emplace(min(stoull(t1, 0, 2), stoull(t2, 0, 2)));
        }
    }

    cout << db.size();
    return 0;
}
