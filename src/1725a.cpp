/*
 * Q1725a - DnC + Greedy
 * Date: 2023.4.24
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> H;

int dnc(int l, int r) {
    if (l == r) return H[l];
    int minh = INT_MAX;
    int ans = 0;
    int m = (l + r) >> 1;
    int i = m, j = m+1;
    while (l <= i && j <= r) {
        minh = min(minh, min(H[i], H[j]));
        ans = max(ans, (j-i+1) * minh);
        if (l == i) ++j;
        else if (j == r) --i;
        else if (H[i-1] < H[j+1]) ++j; else --i;
    }
    return max({ ans, dnc(l, m), dnc(m+1, r) });
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    H.resize(N);
    for (int& h : H) cin >> h;
    cout << dnc(0, N-1);
    return 0;
}
