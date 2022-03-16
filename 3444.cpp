/*
 * Q3444 - Splay tree
 * Date: 2022.3.14
 */

#include<bits/stdc++.h>
using namespace std;

class SplayTree {
    struct Node {
        int val, sz, val_min, val_max;
        bool rev;
        Node *l, *r, *p;
        Node(int v) :
            val(v), rev(false), l(nullptr), r(nullptr), p(nullptr) {}
        ~Node() {
            if (l) delete l;
            if (r) delete r;
        }
        void update() {
            sz = 1;
            val_min = val_max = val;
            if (l) {
                sz += l->sz;
                val_min = min(val_min, l->val_min);
                val_max = max(val_max, l->val_max);
            }
            if (r) {
                sz += r->sz;
                val_min = min(val_min, r->val_min);
                val_max = max(val_max, r->val_max);
            }
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
    void rotate(Node *x) {
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
        if (y)
            y->p = px;
        if (x->p)
            (px == x->p->l ? x->p->l : x->p->r) = x;
        else root = x;
        px->update();
        x->update();
    }
    void splay(Node *x) {
        Node *px, *gx;
        while (x->p) {
            px = x->p;
            gx = px->p;
            if (gx) {
                if ((x == px->l) == (px == gx->l))
                    rotate(px);
                else rotate(x);
            }
            rotate(x);
        }
    }
    Node *find_index(int i) {
        Node *x = root; x->lazy();
        while (true) {
            while (x->l && i < x->l->sz) {
                x = x->l; x->lazy();
            }
            if (x->l)
                i -= x->l->sz;
            if (!i) break;
            i--;
            x = x->r; x->lazy();
        }
        splay(x);
        return x;
    }
    Node *find_value(Node *x, int v) {
        Node *y = nullptr;
        x->lazy();
        if (v == x->val) {
            splay(x);
            return x;
        }
        if (x->l && v >= x->l->val_min && v <= x->l->val_max)
            y = find_value(x->l, v);
        if (!y && x->r && v >= x->r->val_min && v <= x->r->val_max)
            y = find_value(x->r, v);
        return y;
    }
    Node *find_interval(int i, int j) {
        find_index(i-1);
        Node *x = root;
        root = x->r;
        root->p = nullptr;
        find_index(j-i+1);
        x->r = root;
        root->p = x;
        root = x;
        return root->r->l;
    }
    void flip_interval(int i, int j) {
        Node *x = find_interval(i, j);
        x->rev = !x->rev;
    }
public:
    void init(vector<int>& V) {
        N = V.size();
        if (root) delete root;
        root = new Node(0);
        Node *x = root;
        for (int& v : V) {
            x->r = new Node(v);
            x->r->p = x;
            x = x->r;
        }
        x->r = new Node(N+1);
        x->r->p = x;
        x = x->r;
        while (x) {
            x->update();
            x = x->p;
        }
    }
    void solve() {
        for (int i=1; i<=N; ++i) {
            int m = find_interval(i, N)->val_min;
            int j = find_value(root, m)->l->sz;
            flip_interval(i, j);
            cout << j << ' ';
        }
        cout << '\n';
    }
} splayt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int N, M;
    vector<int> V, C;

    cin >> N;
    while (N) {
        V.resize(N);
        M = 0;
        for (int i=0; i<N; ++i) {
            cin >> V[i];
            M = max(M, V[i]);
        }
        C.resize(M+1);
        fill(C.begin(), C.end(), 0);
        for (int i=0; i<N; ++i)
            ++C[V[i]];
        for (int i=0; i<M; ++i)
            C[i+1] += C[i];
        for (int i=N-1; ~i; --i)
            V[i] = C[V[i]]--;

        splayt.init(V);
        splayt.solve();
        cin >> N;
    }
    return 0;
}
