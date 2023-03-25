/*
 * Q10724 - Link-cut tree
 * Date: 2023.3.25
 */

#include<bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;

class LinkCutTree {
    struct Node {
        Node *l, *r, *p;
        ii max_vi;
        int val, id;
        bool rev;
        Node(int i, int c):
            l{0}, r{0}, p{0}, max_vi{c, i}, val{c}, id{i}, rev{false} {}
    };
    vector<Node> nodes;

    bool _is_root(Node *x) {
        return !x->p || (x->p->l != x && x->p->r != x);
    }
    void _update(Node *x) {
        x->max_vi = { x->val, x->id };
        if (x->l) x->max_vi = max(x->max_vi, x->l->max_vi);
        if (x->r) x->max_vi = max(x->max_vi, x->r->max_vi);
    }
    void _lazy(Node *x) {
        if (!x->rev) return;
        swap(x->l, x->r);
        x->rev = false;
        if (x->l) x->l->rev = !x->l->rev;
        if (x->r) x->r->rev = !x->r->rev;
    }
    void _rotate(Node *x) {
        Node *px = x->p;
        _lazy(px); _lazy(x);
        if (x == px->l) {
            px->l = x->r;
            if (x->r) x->r->p = px;
            x->r = px;
        }
        else {
            px->r = x->l;
            if (x->l) x->l->p = px;
            x->l = px;
        }
        x->p = px->p;
        px->p = x;
        if (x->p) {
            if (px == x->p->l) x->p->l = x;
            else if (px == x->p->r) x->p->r = x;
        }
        _update(px); _update(x);
    }
    void _splay(Node *x) {
        while (!_is_root(x)) {
            Node *px = x->p;
            if (!_is_root(px))
                _rotate((x == px->l) == (px == px->p->l)? px : x);
            _rotate(x);
        }
    }
    Node *_access(Node *x) {
        _splay(x); _lazy(x);
        x->r = 0;
        _update(x);

        Node *y = x;
        while (x->p) {
            y = x->p;
            _splay(y); _lazy(y);
            y->r = x;
            _update(y);
            _splay(x);
        }
        return y;
    }
    void _link(Node *x, Node *y) {
        _access(x);
        _access(y);
        x->l = y;
        y->p = x;
        _update(x);
    }
    void _cut(Node *x) {
        _access(x);
        if (x->l) x->l->p = 0;
        x->l = 0;
        _update(x);
    }
    Node *_lca(Node *x, Node *y) {
        _access(x);
        return _access(y);
    }
    void _make_root(Node *x) {
        _access(x);
        x->rev = !x->rev;
    }
    Node *_get_parent(Node *x) {
        _access(x);
        x = x->l;
        if (!x) return 0;
        _lazy(x);
        while (x->r) { x = x->r; _lazy(x); }
        _splay(x);
        return x;
    }
    ii _query(Node *x, Node *y) {
        Node *z = _lca(y, x);
        ii ret = { z->val, z->id };
        _access(x); _splay(z);
        if (z->r) ret = max(ret, z->r->max_vi);
        _access(y); _splay(z);
        if (z->r) ret = max(ret, z->r->max_vi);
        return ret;
    }
public:
    /* prevent reallocation */
    LinkCutTree(int sz) { nodes.reserve(sz); }
    int add_node(int c) {
        int id = nodes.size();
        nodes.emplace_back(id, c);
        return id;
    }
    void link(int u, int v) { _link(&nodes[u], &nodes[v]); }
    void cut(int v) { _cut(&nodes[v]); }
    void make_root(int v) { _make_root(&nodes[v]); }
    int get_parent(int v) { return _get_parent(&nodes[v])->id; }
    ii query(int u, int v) { return _query(&nodes[u], &nodes[v]); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int tc; cin >> tc;
    while (tc--) {
        int N, M; cin >> N >> M;

        int64_t C = 0L;
        vector<ii> edges(2*N + M);
        LinkCutTree lct(2*N + M);
        lct.add_node(-1);

        for (int i = 1; i < N; ++i) {
            int u, c; cin >> u >> c; u <<= 1;
            C += c;
            int t = lct.add_node(c);
            lct.add_node(-1);
            lct.link(t, u);
            lct.link(t+1, t);
            edges[t] = { u, t+1 };
        }

        int64_t ans = 0L;
        while (M--) {
            int u, v, c; cin >> u >> v >> c; u <<= 1; v <<= 1;
            auto [max_c, max_i] = lct.query(u, v);

            if (c < max_c) {
                C += c - max_c;

                auto& [a, b] = edges[max_i];
                lct.cut(lct.get_parent(max_i) == a? b : a);
                lct.cut(max_i);

                int t = lct.add_node(c);
                lct.link(t, u);
                lct.make_root(v);
                lct.link(v, t);
                edges[t] = { u, v };
            }
            ans ^= C;
        }
        cout << ans << '\n';
    }

    return 0;
}
