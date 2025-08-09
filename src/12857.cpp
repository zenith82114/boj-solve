/*
 * Q12857 - query caching
 * Date: 2025.8.9
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

vector<int> pos[600'000];
map<i64, int> cache;

int Hash(const string& a) {
    int x = 0;
    for (auto c : a) x = x*27 + c - 'a' + 1;
    return x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    const int L = s.size();
    for (int i = 0; i < L; ++i)
    for (int d = 1; d <= min(4, L - i); ++d) pos[Hash(s.substr(i, d))].emplace_back(i);

    int q; cin >> q;
    while (q--) {
        string a, b; cin >> a >> b;
        int Ha = Hash(a), Hb = Hash(b);
        if (pos[Ha].size() > pos[Hb].size()) swap(a, b), swap(Ha, Hb);

        i64 key = (i64)Ha<<32|Hb;
        if (cache.find(key) == end(cache)) {
            int ans = L + 1;
            const auto& pa = pos[Ha], & pb = pos[Hb];
            const int La = a.size(), Lb = b.size();

            for (int i : pa) {
                auto f = lower_bound(begin(pb), end(pb), i);
                if (f != begin(pb)) ans = min(ans, max(i + La - *prev(f), Lb));
                if (f != end(pb)) ans = min(ans, max(*f + Lb - i, La));
            }
            cache.emplace(key, ans <= L? ans : -1);
        }
        cout << cache[key] << '\n';
    }

    return 0;
}
