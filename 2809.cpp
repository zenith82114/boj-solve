/*
 * Q2809 - Aho-Corasick alg.
 * Date: 2022.2.9
 */

#include<bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        char chr;
        int pos;
        bool isEntry = false;
        vector<int> chld;
        int prnt = -1, sufx = 0, dict = -1;
        Node(char c, int i) : chr(c), pos(i) {}
    };
    int V;
    vector<Node> nodes;
public:
    void init() {
        V = 1;
        nodes.emplace_back(0, 0);
        nodes[0].sufx = -1;
    }
    void addEntry(string& pattern) {
        int curr = 0, next;
        int P = pattern.length();
        for (int pos=0; pos<P; pos++) {
            next = V;
            for (int& i : nodes[curr].chld) {
                if (nodes[i].chr == pattern[pos]) {
                    next = i;
                    break;
                }
            }
            if (next == V) {
                nodes.emplace_back(pattern[pos], pos);
                nodes[curr].chld.emplace_back(V++);
                nodes.back().prnt = curr;
            }
            curr = next;
        }
        nodes[curr].isEntry = true;
    }
    void makeEdges() {
        queue<int> q;
        int curr, temp;
        q.push(0);
        while (!q.empty()) {
            curr = q.front(); q.pop();
            for (int& i : nodes[curr].chld)
                q.push(i);
            temp = nodes[curr].prnt;
            while (temp > 0 && !nodes[curr].sufx) {
                temp = nodes[temp].sufx;
                for (int& i : nodes[temp].chld) {
                    if (nodes[i].chr == nodes[curr].chr) {
                        nodes[curr].sufx = i;
                        break;
                    }
                }
            }
            temp = nodes[curr].sufx;
            while (temp > 0 && !nodes[temp].isEntry)
                temp = nodes[temp].sufx;
            if (temp > 0)
                nodes[curr].dict = temp;
        }
    }
    void search(string& text, vector<pair<int, int>>& match) {
        int curr = 0, next;
        int T = text.length();
        for (int pos=0; pos<T; pos++) {
            next = 0;
            while (!next) {
                for (int& i : nodes[curr].chld) {
                    if (nodes[i].chr == text[pos]) {
                        next = i;
                        break;
                    }
                }
                if (curr && !next)
                    curr = nodes[curr].sufx;
                else break;
            }
            curr = next;
            if (nodes[next].isEntry)
                match.emplace_back(pos, nodes[next].pos);
            while (nodes[next].dict > 0) {
                next = nodes[next].dict;
                match.emplace_back(pos, nodes[next].pos);
            }
        }
    }
} trie;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<pair<int, int>> v;
    string T, P;
    int N, M, l, nl, nr, cnt;

    cin >> N >> T >> M;
    trie.init();
    while (M--) {
        cin >> P;
        trie.addEntry(P);
    }
    trie.makeEdges();
    trie.search(T, v);

    l = cnt = N;
    for (auto it=v.rbegin(); it!=v.rend(); it++) {
        nr = it->first;
        nl = nr - it->second;
        if (nl < l) {
            cnt -= (nr < l ? nr+1 : l) - nl;
            l = nl;
        }
    }

    cout << cnt << '\n';
    return 0;
}
