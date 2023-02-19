/*
 * Q16994 - Treap
 * Date: 2023.2.19
 */

#include<bits/stdc++.h>
using namespace std;

class Treap {
    struct node {
        int x, y, sz;
        node *l, *r;
        node() = delete;
        node(int x): x(x), y(rand()), sz(1), l(nullptr), r(nullptr) {}
    };
    void upd(node* t) {
        if (!t) return;
        t->sz = 1;
        if (t->l) t->sz += t->l->sz;
        if (t->r) t->sz += t->r->sz;
    }
    void heapify(node* t) {
        if (!t) return;
        node* max = t;
        if (t->l && t->l->y > max->y)
            max = t->l;
        if (t->r && t->r->y > max->y)
            max = t->r;
        if (max != t) {
            swap(t->y, max->y);
            heapify(max);
        }
    }
    node* build(int s, int e) {
        if (s > e) return nullptr;
        int m = (s + e)>>1;
        node* t = new node(m);
        t->l = build(s, m-1);
        t->r = build(m+1, e);
        heapify(t);
        upd(t);
        return t;
    }
    void split(node* t, node*& t1, node*& t2, int n) {
        if (!t) {
            t1 = t2 = nullptr;
            return;
        }
        int k = t->l? t->l->sz : 0;
        if (n <= k)
            split(t->l, t1, t->l, n), t2 = t;
        else
            split(t->r, t->r, t2, n-k-1), t1 = t;
        upd(t);
    }
    void merge(node*& t, node* t1, node* t2) {
        if (!t1 || !t2)
            t = t1? t1 : t2;
        else if (t1->y > t2->y)
            merge(t1->r, t1->r, t2), t = t1;
        else
            merge(t2->l, t1, t2->l), t = t2;
        upd(t);
    }
    int query_util(node* t, int i) {
        int k = t->l? t->l->sz : 0;
        if (i < k)
            return query_util(t->l, i);
        else if (i > k)
            return query_util(t->r, i-k-1);
        else
            return t->x;
    }
public:
    node* root;
    Treap(int N): root(build(0, N-1)) {}
    void move_left(int i, int j) {
        node* t1, * t2;
        split(root, root, t1, i);
        split(t1, t1, t2, j-i+1);
        merge(root, t1, root);
        merge(root, root, t2);
    }
    void move_right(int i, int j) {
        node* t1, * t2;
        split(root, root, t1, i);
        split(t1, t1, t2, j-i+1);
        merge(root, root, t2);
        merge(root, root, t1);
    }
    int query(int i) { return query_util(root, i); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string S; cin >> S;
    int N = S.size();
    Treap tr(N);

    int Q; cin >> Q;
    while (Q--) {
        int q, i, j; cin >> q;
        if (q == 1) {
            cin >> i >> j;
            tr.move_left(i, j);
        }
        else if (q == 2) {
            cin >> i >> j;
            tr.move_right(i, j);
        }
        else {
            cin >> i;
            cout << S[tr.query(i)] << '\n';
        }
    }

    return 0;
}
