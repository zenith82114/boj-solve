/*
 * Q3430 - Greedy + disjoint sets
 * Date: 2023.10.26
 */

#include<bits/stdc++.h>
using namespace std;

int pre[1'000'001];
int par[1'000'001];
int res[1'000'001];

int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int tc; cin >> tc;
    while (tc--) {
        int n, m; cin >> n >> m;

        vector<int> v(m);
        vector<int> zero_pos;
        int j = 0;
        for (int i = 0; i < m; ++i) {
            cin >> v[i];
            if (v[i] == 0) {
                zero_pos.push_back(i);
                for (; j <= i; ++j) par[j] = i;
                j = i+1;
            }
        }
        for (; j <= m; ++j) par[j] = m;

        for (int x = 0; x <= n; ++x) pre[x] = -1;
        for (int i = 0; i < m; ++i) res[i] = 0;

        int sz = 0;
        bool fail = false;

        for (int i = 0; i < m; ++i) {
            int x = v[i];
            if (x != 0) {
                if (!sz || pre[0] < pre[x]) {
                    fail = true;
                    break;
                }
                sz--;
                int j = find(pre[x] + 1);
                if (i < j) {
                    fail = true;
                    break;
                }
                res[j] = x;
                int k = find(j + 1);
                par[j] = k;
            } else sz++;

            pre[x] = i;
        }

        if (fail) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i : zero_pos) cout << res[i] << ' ';
            cout << '\n';
        }
    }

    return 0;
}
