/*
 * Q1391 - Stack
 * Date: 2024.2.25
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int ar[2048], iar[2048];

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> ar[i];
            iar[ar[i]] = i;
        }

        stack<int> ls, rs;
        bitset<2048> lchk, rchk;
        bool ans = true;

        for (int x = 1; x <= n; ++x) {
            int lx = iar[x] > 1? ar[iar[x]-1] : -1;
            int rx = iar[x] < n? ar[iar[x]+1] : -1;
            if (~iar[x]&1) swap(lx, rx);

            if (lx != -1) {
                if (lchk[x]) {
                    if (!ls.empty() && ls.top() == x) ls.pop();
                    else ans = false;
                } else {
                    lchk.set(lx);
                    ls.emplace(lx);
                }
            }
            if (rx != -1) {
                if (rchk[x]) {
                    if (!rs.empty() && rs.top() == x) rs.pop();
                    else ans = false;
                } else {
                    rchk.set(rx);
                    rs.emplace(rx);
                }
            }
            if (!ans) break;
        }
        cout << (ans? "YES" : "NO") << '\n';
    }

    return 0;
}
