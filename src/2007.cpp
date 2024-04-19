/*
 * Q2007 - Bruteforce + mathematics
 * Date: 2024.4.19
 */

#include<bits/stdc++.h>
using namespace std;

class Oracle {
    constexpr static int mu = 1'000'000;
    vector<int> cnt, keys;
    int key_ptr;
public:
    Oracle(const vector<int>& v): cnt(2*mu + 1), keys(v) {
        for (int& k : keys) k += mu;
    }
    void init() {
        key_ptr = 0;
        for (int k : keys) cnt[k] = 0;
        for (int k : keys) ++cnt[k];
    }
    int erase_min() {
        while (!cnt[keys[key_ptr]]) ++key_ptr;
        --cnt[keys[key_ptr]];
        return keys[key_ptr] - mu;
    }
    bool erase(int x) {
        if (x < -mu || x > mu) return false;
        if (!cnt[x + mu]) return false;
        --cnt[x + mu];
        return true;
    }
};

int n;
int s[100][100];

bool chk(int x, Oracle& orc) {
    s[2][1] = x;
    if ((s[1][0] + x - s[2][0]) & 1) return false;
    orc.init();
    orc.erase(x);

    for (int i = 3; i < n; ++i) {
        s[i][0] = orc.erase_min();
        for (int j = 1; j < i-1; ++j) {
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1];
            if (!orc.erase(s[i][j])) return false;
        }
        s[i][i-1] = s[i][i-2] + s[i-1][0] - s[i-2][0];
        if (!orc.erase(s[i][i-1])) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    if (n == 2) {
        int x; cin >> x;
        cout << min(0, x) << ' ' << max(0, x) << '\n';
        return 0;
    }

    vector<int> v(n*(n-1)/2);
    for (int& x : v) cin >> x;
    sort(v.begin(), v.end());
    s[1][0] = v[0]; v.erase(v.begin());
    s[2][0] = v[0]; v.erase(v.begin());

    Oracle orc(v);
    size_t idx = 0;
    while (idx < v.size() && !chk(v[idx], orc)) ++idx;
    if (idx == v.size()) {
        cout << "Impossible\n";
        return 0;
    }

    for (int i = 1; i < n-1; ++i) {
        s[i][i] = s[i][i-1] + s[i+1][i] - s[i+1][i-1];
    }
    s[0][0] = 2 * s[1][0] - s[1][1];
    s[n-1][n-1] = 2 * s[n-1][n-2] - s[n-2][n-2];

    for (int i = 0; i < n; ++i) cout << s[i][i]/2 << ' ';
    return 0;
}
