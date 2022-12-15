/*
 * Q2912 - Ad-hoc query w/ segment tree
 * Date: 2022.7.7
 */

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> color_groups;
inline int get_color_cnt(int i, int j, int c) {
    auto& group = color_groups[c];
    return upper_bound(group.begin(), group.end(), j)
         - lower_bound(group.begin(), group.end(), i);
}

class seg_tree {
    int N;
    vector<int> tree;
    int lc(int n) { return n<<1; }
    int rc(int n) { return (n<<1)|1; }
    void init_util(int n, int s, int e, vector<int>& data) {
        if (s != e) {
            int m = (s+e)>>1;
            init_util(lc(n), s, m, data);
            init_util(rc(n), m+1, e, data);

            if ((e-s+1)/2 < get_color_cnt(s, e, tree[lc(n)]))
                tree[n] = tree[lc(n)];
            else if ((e-s+1)/2 < get_color_cnt(s, e, tree[rc(n)]))
                tree[n] = tree[rc(n)];
            else tree[n] = 0;
        }
        else tree[n] = data[s];
    }
    void query_util(int n, int s, int e, int i, int j, vector<int>& ans) {
        if (s > j || e < i)
            return;
        if (s < i || e > j) {
            int m = (s+e)>>1;
            query_util(lc(n), s, m, i, j, ans);
            query_util(rc(n), m+1, e, i, j, ans);
        }
        else if (tree[n])
            ans.emplace_back(tree[n]);
    }
public:
    seg_tree(vector<int>& data) {
        N = data.size()-1;
        int sz = N;
        if (sz & (sz-1)) {
            for (int i = 1; i < 32; i <<= 1)
                sz |= (sz >> i);
            sz++;
        }
        tree.resize(sz<<1);
        init_util(1, 1, N, data);
    }
    void query(int i, int j, vector<int>& ans) {
        query_util(1, 1, N, i, j, ans);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, C; cin >> N >> C;
    vector<int> data(N+1);
    color_groups.resize(C+1);
    for (int n = 1; n <= N; n++) {
        cin >> data[n];
        color_groups[data[n]].emplace_back(n);
    }
    for (auto& group : color_groups)
        sort(group.begin(), group.end());

    int M; cin >> M;
    seg_tree segt(data);
    vector<int> colors;
    while (M--) {
        int i, j; cin >> i >> j;
        int x = 0;
        colors.clear();

        segt.query(i, j, colors);
        for (int& c : colors) {
            if ((j-i+1)/2 < get_color_cnt(i, j, c)) {
                x = c;
                break;
            }
        }
        if (x)
            cout << "yes " << x << '\n';
        else cout << "no\n";
    }

    return 0;
}
