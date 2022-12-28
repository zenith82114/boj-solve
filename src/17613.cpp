/*
 * Q17613 - Greedy + DnC
 * Date: 2022.12.27
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> v;

int dnc(int x, int y) {
    if (!x && !y) return 0;

    int i = 0;
    for (; i+1 < 32 && v[i+1] <= x; ++i);
    if (y < v[i+1])
        return dnc(x - v[i], y - v[i]) + i;

    int j = i;
    for (; j+1 < 32 && v[j+1] <= y; ++j);

    int ret = 0;
    if (v[j+1] == y+1)
        ret = 1 + (j*(j+1))/2;
    else if (i+1 < y)
        ret = 1 + ((j-1)*j)/2;
    else if (v[i] == x)
        ret = 1 + (i*(i+1))/2;
    return max({ret, dnc(x, v[i+1] -1), dnc(v[j], y)});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    for (int i = 0; i < 32; ++i)
        v.emplace_back((1<<i) -1);

    int T; cin >> T;
    while (T--) {
        int x, y; cin >> x >> y;
        cout << dnc(x, y) << '\n';
    }

    return 0;
}
