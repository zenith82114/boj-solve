/*
 * Q19589 - Splay tree
 * Date: 2024.4.15
 */

#include<bits/stdc++.h>
using namespace std;

class splay_tree {
    struct node {
        node *l, *r, *p;
        int val, sz;
        bool rev;
        node(int v)
        : l(nullptr), r(nullptr), p(nullptr), val(v), sz(1), rev(false) {}
        void update() {
            sz = 1;
            if (l) sz += l->sz;
            if (r) sz += r->sz;
        }
        void lazy() {
            if (!rev) return;
            if (l) l->rev = !l->rev;
            if (r) r->rev = !r->rev;
            swap(l, r);
            rev = false;
        }
    } *root;
    int N;
    vector<int> buf;
    vector<int>::iterator iter;

    void rotate(node *x) {
        node *px = x->p;
        node *y;
        if (x == px->l) {
            px->l = y = x->r;
            x->r = px;
        } else {
            px->r = y = x->l;
            x->l = px;
        }
        x->p = px->p;
        px->p = x;
        if (y) y->p = px;
        if (x->p) (px == x->p->l ? x->p->l : x->p->r) = x;
        else root = x;
        px->update();
        x->update();
    }
    void splay(node *x) {
        node *px, *gx;
        while (x->p) {
            px = x->p;
            gx = px->p;
            if (gx) {
                if ((x == px->l) == (px == gx->l)) rotate(px);
                else rotate(x);
            }
            rotate(x);
        }
    }
    node *find_index(int i) {
        node *x = root; x->lazy();
        while (true) {
            while (x->l && i < x->l->sz) {
                x = x->l; x->lazy();
            }
            if (x->l) i -= x->l->sz;
            if (!i) break;
            i--;
            x = x->r; x->lazy();
        }
        splay(x);
        return x;
    }
    node *find_interval(int i, int j) {
        find_index(i-1);
        node *x = root;
        root = x->r;
        root->p = nullptr;
        find_index(j-i+1);
        x->r = root;
        root->p = x;
        root = x;
        return root->r->l;
    }
    void flip_interval(int i, int j) {
        node *x = find_interval(i, j);
        x->rev = !x->rev;
    }
    void read_util(node *x) {
        if (!x) return;
        x->lazy();
        read_util(x->l);
        if (x->val > 0 && x->val <= N)
            buf.emplace_back(x->val);
        read_util(x->r);
    }
    void write_util(node *x) {
        if (!x) return;
        x->lazy();
        write_util(x->l);
        if (x->val > 0 && x->val <= N)
            x->val = *(iter++);
        write_util(x->r);
    }
    void print_util(node *x) {
        if (!x) return;
        x->lazy();
        print_util(x->l);
        if (x->val > 0 && x->val <= N)
            cout << (x->val) << ' ';
        print_util(x->r);
    }

public:
    splay_tree(int _N): N(_N) {
        node *x = root = new node(0);
        for (int i = 1; i <= N+1; ++i) {
            x->r = new node(i);
            x->r->p = x;
            x = x->r;
        }
        for (; x; x = x->p) x->update();
    }
    void shift_interval_left(int i, int j) {
        if (i == 1) return;
        flip_interval(1, j);
        flip_interval(1, j-i+1);
        flip_interval(j-i+2, j);
    }
    void shift_interval_right(int i, int j) {
        if (j == N) return;
        flip_interval(i, N);
        flip_interval(i, i+N-j-1);
        flip_interval(i+N-j, N);
    }
    void riffle(int i, int j) {
        buf.clear();
        node *x = find_interval(i, j);
        read_util(x);

        int k = buf.size();
        vector<int> temp;
        for (int l = 0, r = (k+1)/2; r < k; ++l, ++r) {
            temp.emplace_back(buf[l]);
            temp.emplace_back(buf[r]);
        }
        if (k&1) temp.emplace_back(buf[(k-1)/2]);
        buf.swap(temp);

        iter = buf.begin();
        write_util(x);
    }
    void print() { print_util(root); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q; cin >> n >> q;
    splay_tree splayt(n);
    while (q--) {
        int op, i, j; cin >> op >> i >> j;
        if (op == 1) splayt.shift_interval_left(i, j);
        else
        if (op == 2) splayt.shift_interval_right(i, j);
        else
        splayt.riffle(i, j);
    }
    splayt.print();
    return 0;
}
