/*
 * Q16901 - DnC + Trie
 * Date: 2023.5.1
 */

#include<bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        int l, r;
        Node(): l(-1), r(-1) {}
    };
    vector<Node> nodes;
public:
    Trie(): nodes(1) {}
    void insert(int x) {
        int i = 0;
        for (int b = 1<<29; b; b >>= 1) {
            if (x & b) {
                if (nodes[i].r == -1) {
                    nodes[i].r = nodes.size();
                    nodes.emplace_back();
                }
                i = nodes[i].r;
            } else {
                if (nodes[i].l == -1) {
                    nodes[i].l = nodes.size();
                    nodes.emplace_back();
                }
                i = nodes[i].l;
            }
        }
    }
    int query(int x) {
        int i = 0, y = 0;
        for (int b = 1<<29; b; b >>= 1) {
            auto& [l, r] = nodes[i];
            if ((x & b && r != -1) || (~x & b && l == -1)) {
                i = r; y |= b;
            } else i = l;
        }
        return x ^ y;
    }
};

vector<int> A;

int64_t dnc(int l, int r, int b) {
    if (l == r || !b) return 0;
    if (A[l] & b || ~A[r] & b) return dnc(l, r, b>>1);

    int m = l; while (m < r && ~A[m+1] & b) ++m;
    int64_t ret = dnc(l, m, b>>1) + dnc(m+1, r, b>>1);

    Trie tr;
    for (int i = l; i <= m; ++i) tr.insert(A[i]);
    int w = INT_MAX;
    for (int i = m+1; i <= r; ++i) w = min(w, tr.query(A[i]));
    return ret + w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    A.resize(N);
    for (int& a : A) cin >> a;
    sort(A.begin(), A.end());
    cout << dnc(0, N-1, 1<<29);
    return 0;
}
