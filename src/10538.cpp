/*
 * Q10538 - Aho-Corasick + KMP
 * Date: 2023.8.14
 */

#include<bits/stdc++.h>
using namespace std;

int a[2000][2000] {};
int b[2000] {};
int ff[2000] {};

class Trie {
    struct Node {
        Node *chld[2];
        Node *prnt, *sufx;
        int chr, pid;
        Node(int c): chld(), prnt(0), sufx(0), chr(c), pid(-1) {}
    };
    Node *root;
public:
    void init() { root = new Node(-1); }
    void insert(const string& pattern, int pid) {
        Node *cur = root;
        for (const char& p : pattern) {
            int chr = p == 'o'? 0 : 1;
            Node *&nxt = cur->chld[chr];
            if (!nxt) {
                nxt = new Node(chr);
                nxt->prnt = cur;
            }
            cur = nxt;
        }
        cur->pid = pid;
    }
    void build() {
        queue<Node *> q;
        for (auto tmp : root->chld) if (tmp) {
            tmp->sufx = root;
            q.emplace(tmp);
        }
        while (!q.empty()) {
            Node *cur = q.front(); q.pop();
            if (cur->chld[0]) q.emplace(cur->chld[0]);
            if (cur->chld[1]) q.emplace(cur->chld[1]);

            Node *tmp = cur->prnt;
            while (tmp != root && !cur->sufx) {
                tmp = tmp->sufx;
                cur->sufx = tmp->chld[cur->chr];
            }
            if (!cur->sufx) cur->sufx = root;
        }
    }
    vector<pair<int, int> > search(const string& text) {
        vector<pair<int, int> > matches;
        Node *cur = root;

        for (int i = 0; i < (int)text.size(); ++i) {
            int chr = text[i] == 'o'? 0 : 1;
            while (cur != root && !cur->chld[chr]) cur = cur->sufx;
            if (cur->chld[chr]) cur = cur->chld[chr];
            if (cur->pid != -1) matches.emplace_back(i, cur->pid);
        }
        return matches;
    }
} trie;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int hp, wp, hm, wm; cin >> hp >> wp >> hm >> wm;
    vector<string> v(hp); for (auto& p : v) cin >> p;

    auto sv(v); sv.emplace_back();
    sort(sv.begin(), sv.end());
    sv.erase(unique(sv.begin(), sv.end()), sv.end());
    trie.init();
    for (int i = 1; i < (int)sv.size(); ++i) trie.insert(sv[i], i);
    trie.build();

    for (int i = 0; i < hm; ++i) {
        string t; cin >> t;
        auto matches = trie.search(t);
        for (const auto& [j, pid] : matches) a[i][j] = pid;
    }

    for (int i = 0; i < hp; ++i) {
        b[i] = lower_bound(sv.begin(), sv.end(), v[i]) - sv.begin();
    }
    for (int i = 1, j = 0; i < hp; ++i) {
        while (j && b[i] != b[j]) j = ff[j-1];
        if (b[i] == b[j]) ++j;
        ff[i] = j;
    }

    int ans = 0;
    for (int col = wp-1; col < wm; ++col) {
        for (int i = 0, j = 0; i < hm; ++i) {
            while (j && a[i][col] != b[j]) j = ff[j-1];
            if (a[i][col] == b[j]) ++j;
            if (j == hp) ++ans, j = ff[j-1];
        }
    }

    cout << ans;
    return 0;
}
