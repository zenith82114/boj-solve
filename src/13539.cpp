/*
 * Q13539 - Link-cut tree
 * Date: 2023.3.21
 */

#include<bits/stdc++.h>
using namespace std;

class LinkCutTree {
    struct Node {
        Node *l = 0, *r = 0, *p = 0;
    };
    vector<Node> nodes;

    bool _is_root(Node *x) {
        return !x->p || (x->p->l != x && x->p->r != x);
    }
    void _rotate(Node *x) {
        Node *px = x->p;
        Node *y;
        if (x == px->l) {
            px->l = y = x->r;
            x->r = px;
        }
        else {
            px->r = y = x->l;
            x->l = px;
        }
        x->p = px->p;
        px->p = x;
        if (y) y->p = px;
        if (x->p) {
            if (px == x->p->l) x->p->l = x;
            else if (px == x->p->r) x->p->r = x;
        }
    }
    void _splay(Node *x) {
        while (!_is_root(x)) {
            Node *px = x->p;
            if (!_is_root(px)) {
                if ((x == px->l) == (px == px->p->l)) _rotate(px);
                else _rotate(x);
            }
            _rotate(x);
        }
    }
    Node* _access(Node *x) {
        _splay(x);
        x->r = 0;
        Node *y = x;
        while (x->p) {
            Node *px = x->p;
            y = px;
            _splay(px);
            px->r = x;
            _splay(x);
        }
        return y;
    }
    void _link(Node *x, Node *y) {
        _access(x);
        _access(y);
        x->l = y;
        y->p = x;
    }
    void _cut(Node *x) {
        _access(x);
        x->l->p = 0;
        x->l = 0;
    }
    Node *_lca(Node *x, Node *y) {
        _access(x);
        return _access(y);
    }
public:
    LinkCutTree(int N): nodes(N) {}
    void link(int u, int v) { _link(&nodes[u], &nodes[v]); }
    void cut(int v) { _cut(&nodes[v]); }
    int lca(int u, int v) { return _lca(&nodes[u], &nodes[v]) - &nodes[0]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;
    LinkCutTree lct(N+1);

    while (M--) {
        int q, u, v; cin >> q;
        switch (q) {
            case 1:
            cin >> u >> v; lct.link(u, v); break;
            case 2:
            cin >> v; lct.cut(v); break;
            case 3:
            cin >> u >> v; cout << lct.lca(u, v) << '\n'; break;
        }
    }

    return 0;
}
