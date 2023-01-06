/*
 * Q13576 - Z function
 * Date: 2023.1.5
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string S; cin >> S;
    int N = S.size();

    vector<int> z(N, 0);
    z[0] = N;
    int l = 0, r = 0;
    for (int i = 1; i < N; ++i) {
        if (i <= r)
            z[i] = min(z[i - l], r - i +1);
        while (i + z[i] < N && S[z[i]] == S[i + z[i]]) z[i]++;
        if (r < i + z[i] -1) {
            r = i + z[i] -1;
            l = i;
        }
    }

    auto zs = z;
    sort(zs.begin(), zs.end());
    vector<pair<int, int>> ans;
    for (int i = N-1; ~i; --i) if (i + z[i] == N)
        ans.emplace_back(z[i], zs.end() - lower_bound(zs.begin(), zs.end(), z[i]));

    cout << ans.size() << '\n';
    for (const auto& [l, c] : ans) cout << l << ' ' << c << '\n';

    return 0;
}
