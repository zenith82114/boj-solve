/*
 * Q3764 - Backtracking
 * Date: 2023.7.3
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int a[16];
i64 l[16], r[16];

bool backtrack(int i, int k) {
    if (l[i-1] >= r[i-1]) return false;
    if (i == k) return l[i-1] % (r[i-1] - l[i-1]) == 0;

    a[i] = a[i-1];
    l[i] = l[i-1] * (1 + a[i]);
    r[i] = r[i-1] * a[i];
    i64 nl = l[i-1], nr = r[i-1];
    for (int j = i; j <= k; ++j) {
        nl *= 1 + a[i];
        nr *= a[i];
    }
    while (nl >= nr) {
        if (backtrack(i+1, k)) return true;
        a[i]++;
        l[i] = l[i-1] * (1 + a[i]);
        r[i] = r[i-1] * a[i];
        nl = l[i-1];
        nr = r[i-1];
        for (int j = i; j <= k; ++j) {
            nl *= 1 + a[i];
            nr *= a[i];
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    int k = 1; while (1<<k < n) ++k;
    a[0] = 1;
    l[0] = 1;
    r[0] = n;
    while (!backtrack(1, k)) ++k;
    cout << k;
    return 0;
}
