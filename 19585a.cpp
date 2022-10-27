/*
 * Q19585a - Double hashing
 * Date: 2022.10.28
 */

#include<bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;

const int M = 1'000'000'007;
const int p1 = 31;
const int p2 = 29;
const int p1_inv = 129'032'259;
const int p2_inv = 758'620'695;

int p1_exp[1'000], p2_exp[1'000];

inline int enc(const char &c) { return c - 'a' + 1; }

ii my_hash(const string &s) {
    int L = s.size();
    int h1 = 0, h2 = 0;
    for (int i = 0; i < L; ++i) {
        h1 = (h1 + (enc(s[i]) * 1ll * p1_exp[i])) % M;
        h2 = (h2 + (enc(s[i]) * 1ll * p2_exp[i])) % M;
    }
    return make_pair(h1, h2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    p1_exp[0] = 1;
    for (int i = 1; i < 1'000; ++i)
        p1_exp[i] = (p1 * 1ll * p1_exp[i-1]) % M;
    p2_exp[0] = 1;
    for (int i = 1; i < 1'000; ++i)
        p2_exp[i] = (p2 * 1ll * p2_exp[i-1]) % M;

    int C, N; cin >> C >> N;
    set<ii> HC, HN;
    string s;
    for (int c = 0; c < C; ++c) {
        cin >> s;
        HC.emplace(my_hash(s));
    }
    for (int n = 0; n < N; ++n) {
        cin >> s;
        HN.emplace(my_hash(s));
    }
    assert((int)HC.size() == C && "color collision\n");
    assert((int)HN.size() == N && "nickname collision\n");

    int Q; cin >> Q;
    while (Q--) {
        cin >> s;
        int L = s.size();
        if (L == 1) { cout << "No\n"; continue; }

        const int b = max(1, L - 1'000);
        const int e = min(1'000, L - 1);

        ii hc = my_hash(s.substr(0, b));
        ii hn = my_hash(s.substr(b));

        if (HC.find(hc) != HC.end() && HN.find(hn) != HN.end()) {
            cout << "Yes\n";
            continue;
        }

        int i;
        for (i = b; i < e; ++i) {
            int v = enc(s[i]);
            int &hc1 = hc.first;
            hc1 = (hc1 + (v * 1ll * p1_exp[i])) % M;
            int &hc2 = hc.second;
            hc2 = (hc2 + (v * 1ll * p2_exp[i])) % M;

            int &hn1 = hn.first;
            hn1 = (hn1 + M - v) % M;
            hn1 = (hn1 * 1ll * p1_inv) % M;
            int &hn2 = hn.second;
            hn2 = (hn2 + M - v) % M;
            hn2 = (hn2 * 1ll * p2_inv) % M;

            if (HC.find(hc) != HC.end() && HN.find(hn) != HN.end()) {
                cout << "Yes\n";
                break;
            }
        }
        if (i == e) cout << "No\n";
    }

    return 0;
}
