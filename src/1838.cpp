/*
 * Q1838 - Sorting
 * Date: 2023.12.5
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<pair<int, int> > v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first; v[i].second = i;
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, v[i].second - i);
    }
    cout << ans;
    return 0;
}
