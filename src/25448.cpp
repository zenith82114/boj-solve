/*
 * Q25448 - Erdos-Ginzburg-Ziv theorem
 * Date: 2026.4.6
 *
 * O(n log n) solution from http://arxiv.org/abs/2208.07728
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int mul_mod(int a, int b, int p) { return 1ll*a*b%p; }

int inv_mod(int a, int p) {
    int b = 1;
    for (int e = p - 2; e; e >>= 1) {
        if (e&1) b = mul_mod(a, b, p);
        a = mul_mod(a, a, p);
    }
    return b;
}

int find_t(int p, const vector<char>& T, int d, int s) {
    int lo = mul_mod(s, inv_mod(d, p), p), hi = p;
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        (T[mul_mod(m, d, p)] ? lo : hi) = m;
    }
    return mul_mod(hi, d, p);
}

vector<char> solve(int, const vector<int>&);

vector<char> solve_prime(int p, const vector<int>& a) {
    vector<int> k(a.size());
    iota(k.begin(), k.end(), 0);
    sort(k.begin(), k.end(), [&](int i, int j) {
        return a[i] % p < a[j] % p; });

    vector<char> L(a.size(), 0);
    for (int i = 0; i < p; ++i) {
        if (a[k[i]] % p == a[k[i + p - 1]] % p) {
            for (int j = i; j < i + p; ++j) L[k[j]] = 1;
            return L;
        }
    }

    int s = 0;
    for (int i = 0; i < p; ++i) s = (s + a[k[i]]) % p;
    vector<char> T(p, 0); T[s] = 1;
    vector<int> P(p, -1);

    for (int i = 0; i < p - 1; ++i) {
        if (T[0]) break;
        int d = (a[k[i + p]] % p) - (a[k[i]] % p);
        int t = find_t(p, T, d, s);
        T[t] = 1;
        P[t] = i;
    }

    for (int i = 0; i < p; ++i) L[k[i]] = 1;
    for (int c = 0; s != c;) {
        int i = P[c];
        L[k[i + p]] = 1;
        L[k[i]] = 0;
        int d = (a[k[i + p]] % p) - (a[k[i]] % p);
        c = (c - d + p) % p;
    }
    return L;
}

vector<char> solve_composite(int p, int q, const vector<int>& a) {
    vector<int> S(p - 1); iota(S.begin(), S.end(), 0);
    vector<vector<int>> T(2*q);

    for (int i = 1; i < 2*q; ++i) {
        for (int j = i*p - 1; j < (i + 1)*p - 1; ++j) S.push_back(j);
        vector<int> b;
        for (int j : S) b.push_back(a[j]);
        auto ret = solve(p, b);
        vector<int> nextS;
        for (int j = 0; j < 2*p - 1; ++j) {
            if (ret[j]) T[i].push_back(S[j]);
            else nextS.push_back(S[j]);
        }
        S.swap(nextS);
    }

    vector<char> L(2*p*q - 1, 0);
    vector<int> b;
    for (int i = 1; i < 2*q; ++i) {
        i64 s = 0; for (int j : T[i]) s += a[j];
        b.push_back(s/p);
    }
    auto ret = solve(q, b);
    for (int i = 1; i < 2*q; ++i) if (ret[i - 1]) {
        for (int j : T[i]) L[j] = 1;
    }
    return L;
}

vector<char> solve(int n, const vector<int>& a) {
    if (n == 1) return { 1 };
    for (int i = 2; i < n; ++i) if (n % i == 0) {
        return solve_composite(i, n/i, a);
    }
    return solve_prime(n, a);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> a(2*n - 1); for (int& x : a) cin >> x;
    auto ret = solve(n, a);
    for (int i = 0; i < 2*n - 1; ++i) if (ret[i]) cout << a[i] << ' ';

    return 0;
}
