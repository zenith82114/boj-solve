/*
 * Q19585 - Trie
 * Date: 2023.12.26
 */

#include<bits/stdc++.h>
using namespace std;

class Trie {
    int chld[4'000'000][26];
    bitset<4'000'000> eos;
    int sz;
public:
    Trie(): sz(1) {
        memset(chld[0], 0, 26 * sizeof(int));
    }
    void insert(const string& s) {
        int x = 0;
        for (char c : s) {
            int& y = chld[x][c - 'a'];
            if (!y) {
                y = sz++;
                memset(chld[y], 0, 26 * sizeof(int));
            }
            x = y;
        }
        eos.set(x);
    }
    void query(const string& s, bitset<2'000>& v) {
        int x = 0, i = 0;
        for (char c : s) {
            int y = chld[x][c - 'a'];
            if (!y) break;
            if (eos[y]) v.set(i++); else v.reset(i++);
            x = y;
        }
        int n = s.size();
        for (; i < n; ++i) v[i] = false;
    }
} trie1, trie2;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int C, N; cin >> C >> N;
    string s;
    while (C--) {
        cin >> s;
        trie1.insert(s);
    }
    while (N--) {
        cin >> s; reverse(s.begin(), s.end());
        trie2.insert(s);
    }

    int Q; cin >> Q;
    bitset<2'000> v1, v2;
    while (Q--) {
        cin >> s;
        trie1.query(s, v1);
        reverse(s.begin(), s.end());
        trie2.query(s, v2);

        int sz = s.size();
        bool flag = false;
        for (int i = 0; i+1 < sz; ++i) {
            if (v1[i] && v2[sz-2-i]) { flag = true; break; }
        }
        cout << (flag? "Yes\n" : "No\n");
    }

    return 0;
}
