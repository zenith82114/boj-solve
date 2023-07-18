/*
 * Q1627 - Sprague-Grundy theorem
 * Date: 2023.7.18
 */

#include<bits/stdc++.h>
using namespace std;

char bd[3030] { 'P', '.', '.', };
int mem[3030];

int sg(int x) {
    if (x < 0) return 0;
    int& ans = mem[x];
    if (ans != -1) return ans;
    set<int> s;
    for (int i = 0; i <= x>>1; ++i)
        s.emplace(sg(i-2) ^ sg(x-i-3));
    ans = 0;
    while (s.count(ans)) ++ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    memset(mem, -1, sizeof mem);
    mem[0] = 0; mem[1] = mem[2] = mem[3] = 1;

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> bd[i+3];
    bd[N+3] = bd[N+4] = '.'; bd[N+5] = 'P';

    int g0 = 0;
    int l = 1, r = 1;
    while (r < N+6) {
        while (bd[r] == '.') ++r;
        g0 ^= sg(r-l-4);
        l = ++r;
    }

    vector<int> pos;

    for (int i = 3; i < N+3; ++i) {
        if ((bd[i-2] == 'P' && bd[i-1] == 'P' && bd[i] == '.') ||
            (bd[i-1] == 'P' && bd[i] == '.' && bd[i+1] == 'P') ||
            (bd[i] == '.' && bd[i+1] == 'P' && bd[i+2] == 'P'))
            pos.emplace_back(i-2);
    }
    if (!pos.empty()) {
        cout << "WINNING\n";
        for (int i : pos) cout << i << ' ';
        return 0;
    }

    l = 1, r = 1;
    while (r < N+6) {
        while (bd[r] == '.') ++r;
        const int g = sg(r-l-4);
        for (int i = l+2; i < r-2; ++i) {
            if ((g0 ^ g) == (sg(i-l-4) ^ sg(r-i-5)))
                pos.emplace_back(i-2);
        }
        l = ++r;
    }
    if (!pos.empty()) {
        cout << "WINNING\n";
        for (int i : pos) cout << i << ' ';
    }
    else cout << "LOSING\n";
    return 0;
}
