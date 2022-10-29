/*
 * Q1071 - Greedy
 * Date: 2022.10.29
 */

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<int> cnt(1'024);
    int N; cin >> N;
    for (int n = 0; n < N; ++n) {
        int a; cin >> a;
        ++cnt[a];
    }

    int p = -2;
    for (int n = N; n; --n) {
        int a = 0;
        while (!cnt[a] || a == p +1 || (cnt[a] != n && cnt[a] + cnt[a +1] == n)) ++a;
        --cnt[a];
        p = a;
        cout << a << ' ';
    }

    return 0;
}
