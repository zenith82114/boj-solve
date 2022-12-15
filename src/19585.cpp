/*
 * Q19585 - Trie
 * Date: 2022.9.8
 */

#include<bits/stdc++.h>
using namespace std;

class Trie {
    bool eos = false;
    map<char, Trie *> chld;
public:
    void insert(const string &s) {
        Trie *curr = this;
        for (const char &c : s) {
            if (curr->chld.find(c) == curr->chld.end())
                curr->chld[c] = new Trie;
            curr = curr->chld[c];
        }
        curr->eos = true;
    }
    void insert_rev(const string &s) {
        Trie *curr = this;
        for (auto c = s.rbegin(); c != s.rend(); ++c) {
            if (curr->chld.find(*c) == curr->chld.end())
                curr->chld[*c] = new Trie;
            curr = curr->chld[*c];
        }
        curr->eos = true;
    }
    void query(const string &s, vector<bool> &v) {
        Trie *curr = this;
        int sz = s.size();
        fill(v.begin(), v.begin() + sz, false);
        for (int i = 0; i < sz; ++i) {
            if (curr->chld.find(s[i]) == curr->chld.end())
                return;
            curr = curr->chld[s[i]];
            v[i] = curr->eos;
        }
    }
    void query_rev(const string &s, vector<bool> &v) {
        Trie *curr = this;
        int sz = s.size();
        fill(v.begin(), v.begin() + sz, false);
        for (int i = sz -1; ~i; --i) {
            if (curr->chld.find(s[i]) == curr->chld.end())
                return;
            curr = curr->chld[s[i]];
            v[i] = curr->eos;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    constexpr int MAX_LEN = 2'000;

    int C, N; cin >> C >> N;
    string s;
    Trie trie1;
    while (C--) {
        cin >> s;
        trie1.insert(s);
    }
    Trie trie2;
    while (N--) {
        cin >> s;
        trie2.insert_rev(s);
    }

    int Q; cin >> Q;
    vector<bool> v1(MAX_LEN), v2(MAX_LEN);
    while (Q--) {
        cin >> s;
        trie1.query(s, v1);
        trie2.query_rev(s, v2);

        int sz = s.size();
        bool flag = false;
        for (int i = 0; !flag && i +1 < sz; ++i)
            flag = v1[i] && v2[i +1];
        cout << (flag? "Yes\n" : "No\n");
    }

    return 0;
}
