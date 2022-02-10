/*
 * Q2820 - Segment tree + Euler tour technique
 * Date: 2022.2.10
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> ini, etr;
vector<vector<int>> adj;
vector<pair<int, int>> seg;

void dfs(int pu, int u, int& cnt) {
    etr[cnt] = ini[u];
    seg[u].first = cnt++;
    for (int& v : adj[u]) {
        if (v != pu)
            dfs(u, v, cnt);
    }
    etr[cnt] = ini[u];
    seg[u].second = cnt++;
}

class SegTree {
    int N;
    vector<int> A;
    constexpr int ceilPow2(int n) {
        if (n & (n-1)) {
            for (int i=1; i<32; i<<=1)
                n |= (n>>i);
            return n+1;
        }
        return n;
    }
    int lChild(int n) { return n<<1; }
    int rChild(int n) { return n<<1 | 1; }
    void addSegUtil(int n, int l, int r, int i, int j, int x) {
        int m;
        if (l != i || r != j) {
            m = (l+r)/2;
            if (j <= m)
                addSegUtil(lChild(n), l, m, i, j, x);
            else if (m < i)
                addSegUtil(rChild(n), m+1, r, i, j, x);
            else {
                addSegUtil(lChild(n), l, m, i, m, x);
                addSegUtil(rChild(n), m+1, r, m+1, j, x);
            }
        }
        else A[n] += x;
    }
public:
    void init(vector<int>& etr) {
        int n, l, m, r;
        N = etr.size();
        A.assign(ceilPow2(N)<<1, 0);
        for (int i=0; i<N; i++) {
            n = 1, l = 0, r = N-1;
            while (l < r) {
                m = (l+r)/2;
                if (m < i) {
                    n = rChild(n);
                    l = m+1;
                }
                else {
                    n = lChild(n);
                    r = m;
                }
            }
            A[n] = etr[i];
        }
    }
    void addSeg(int i, int j, int x) {
        if (i > j)
            return;
        addSegUtil(1, 0, N-1, i, j, x);
    }
    int query(int i) {
        int n = 1, l = 0, m, r = N-1;
        int ret = A[1];
        while (l < r) {
            m = (l+r)/2;
            if (m < i) {
                n = rChild(n);
                l = m+1;
            }
            else {
                n = lChild(n);
                r = m;
            }
            ret += A[n];
        }
        return ret;
    }
} segt;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int N, M, v, w, x, cnt;
    char c;

    cin >> N >> M;
    ini.resize(N+1);
    adj.resize(N+1);
    cin >> ini[1];
    for (v=2; v<=N; v++) {
        cin >> ini[v] >> w;
        adj[v].emplace_back(w);
        adj[w].emplace_back(v);
    }

    etr.resize(N<<1);
    seg.resize(N+1);
    cnt = 0;
    dfs(0, 1, cnt);

    segt.init(etr);
    while (M--) {
        cin >> c;
        if (c == 'p') {
            cin >> v >> x;
            segt.addSeg(seg[v].first+1, seg[v].second-1, x);
        }
        else if (c == 'u') {
            cin >> v;
            cout << segt.query(seg[v].first) << '\n';
        }
    }

    return 0;
}
