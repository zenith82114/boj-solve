/*
 * Q16127 - directed MST; subquadratic
 * Date: 2025.5.18
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int MAXN = 604;

struct edge {
    int from, to, cost;
    edge() {}
    edge(int x, int y, int w): from(x), to(y), cost(w) {}
};

class pairing_heap {
    struct node {
        edge e;
        i64 delta = 0; // lazy propagation
        node *chld = nullptr, *sibl = nullptr;
        node(int x, int y, int w) : e(x, y, w) {}
        node(const edge& _e) : e(_e) {}
        ~node() {
            if (chld) delete chld;
            if (sibl) delete sibl;
        }
    };
    node* root = nullptr;
    size_t sz = 0;
    node* merge(node* x, node* y) {
        if (!x) return y;
        if (!y) return x;
        if (x->e.cost + x->delta > y->e.cost + y->delta) swap(x, y);
        y->delta -= x->delta;
        y->sibl = x->chld;
        x->chld = y;
        return x;
    }
public:
    size_t size() const { return sz; }
    i64& delta() {
        // assert(root);
        return root->delta;
    }
    edge top() const {
        // assert(root);
        return root->e;
    }
    void emplace(int x, int y, int w) {
        ++sz;
        root = merge(root, new node(x, y, w));
    }
    void pop() {
        // assert(root && sz > 0);
        --sz;
        node* x = nullptr;
        node* s = root->chld;
        root->chld = nullptr;

        while (s) {
            node *a = s;
            s = s->sibl;
            a->sibl = nullptr;
            a->delta += root->delta;
            node *b = nullptr;
            if (s) {
                b = s;
                s = s->sibl;
                b->sibl = nullptr;
                b->delta += root->delta;
            }
            a = merge(a, b);
            if (!x) x = a;
            else {
                a->sibl = x->sibl;
                x->sibl = a;
            }
        }
        root->chld = nullptr;
        root->sibl = nullptr;
        delete root;
        root = nullptr;

        while (x) {
            node* a = x;
            x = x->sibl;
            a->sibl = nullptr;
            root = merge(a, root);
        }
    }
    void meld(pairing_heap& h) {
        sz += h.sz;
        h.sz = 0;
        root = merge(root, h.root);
        h.root = nullptr;
    }
};

pairing_heap heap[MAXN];
int uf[MAXN], uf_full[MAXN]; // union-find with and without path compression
int vis[MAXN] {};
edge sel[MAXN];
char check[MAXN] {};

int qty[304];
int price[304][304];

int find(int x) {
    if (uf[x] == -1) return x;
    return uf[x] = find(uf[x]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int x = 1; x <= n; ++x) cin >> qty[x];
    for (int x = 0; x <= n; ++x)
    for (int y = 1; y <= n; ++y) {
        cin >> price[x][y];
        if (x != y) heap[y].emplace(x, y, price[x][y]);
    }
    memset(uf, -1, sizeof(uf));
    memset(uf_full, -1, sizeof(uf_full));

    int c = 1, pc = n + 1;
    vis[0] = 1;

    for (int x_ = 0; x_ <= n; ++x_) if (!vis[x_]) {
        ++c;
        int x = x_;
        while (vis[x] == 0 || vis[x] == c) {
            if (vis[x] == c) {
                int nx = pc++;
                for (int y = x; y != nx; y = find(sel[y].from)) {
                    heap[y].delta() = -sel[y].cost;
                    heap[nx].meld(heap[y]);
                    uf[y] = uf_full[y] = nx;
                }
                x = nx;
            }

            assert(!vis[x]);
            vis[x] = c;
            assert(find(x) == x);
            while (heap[x].size() && find(heap[x].top().from) == x) {
                heap[x].pop();
            }
            assert(heap[x].size());
            sel[x] = heap[x].top();
            x = find(sel[x].from);
        }
    }

    i64 ans = 0;
    for (int x = pc - 1; x >= 0; --x) {
        if (x == 0 || check[x]) continue;
        for (int y = sel[x].to; y != -1 && !check[y]; y = uf_full[y]) {
            check[y] = 1;
        }
        ans += sel[x].cost;
    }
    for (int y = 1; y <= n; ++y) {
        int mp = INT32_MAX;
        for (int x = 0; x <= n; ++x) mp = min(mp, price[x][y]);
        ans += 1ll * (qty[y] - 1) * mp;
    }
    cout << ans;
    return 0;
}
