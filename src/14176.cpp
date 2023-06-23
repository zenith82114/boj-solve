/*
 * Q14176 - Centroid DnC + FFT
 * Date: 2023.6.23
 */

#include<bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using cpx = complex<double>;
const double PI = acos(-1.);

vector<int> adj[100'001];
int sz[100'001];
bool sel[100'001];
i64 cnt[100'000];

void fft(vector<cpx>& f, bool inv = false) {
    int N = f.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int t = N>>1;
        for (; j & t; t >>= 1) j ^= t;
        j ^= t;
        if (i < j) swap(f[i], f[j]);
    }

    vector<cpx> roots(N>>1);
    double theta = (inv? -2. : 2.) * PI / N;
    for (int i = 0; i < N>>1; ++i) roots[i] = polar(1., i * theta);

    for (int n = 1; n < N; n <<= 1) {
        int step = (N>>1) / n;
        for (int m = 0; m < N; m += n<<1) {
            for (int i = 0, j = n; i < n; ++i, ++j) {
                cpx a = f[m | i];
                cpx b = f[m | j] * roots[i * step];
                f[m | i] = a + b;
                f[m | j] = a - b;
            }
        }
    }
    if (inv) for (cpx& a : f) a /= N;
}

vector<i64> convolve(const vector<i64>& f, const vector<i64>& g) {
    vector<cpx> f0(f.begin(), f.end()), g0(g.begin(), g.end());
    int a = f.size(), b = g.size();
    int n = 1; while (n < a + b - 1) n <<= 1;
    f0.resize(n); fft(f0);
    g0.resize(n); fft(g0);
    for (int i = 0; i < n; ++i) f0[i] *= g0[i];
    fft(f0, true);
    vector<i64> h(a + b - 1);
    for (int i = 0; i < a + b - 1; ++i) h[i] = llround(f0[i].real());
    return h;
}

int dfs(int px, int x, int d, vector<i64>& f) {
    if ((int)f.size() == d) f.emplace_back(0);
    f[d]++;
    sz[x] = 1;
    for (int y : adj[x]) if (y != px && !sel[y])
        sz[x] += dfs(x, y, d+1, f);
    return sz[x];
}

int ct(int px, int x, int m) {
    for (int y : adj[x]) if (y != px && !sel[y] && sz[y] > m)
        return ct(x, y, m);
    return x;
}

vector<i64> ctd(int pc, int x) {
    vector<i64> fx { 0 };
    int c = ct(pc, x, dfs(pc, x, 1, fx)>>1);
    sel[c] = true;

    vector<vector<i64> > v;
    for (int y : adj[c]) if (!sel[y]) v.emplace_back(ctd(c, y));
    sort(v.begin(), v.end(), [] (const vector<i64>& f1, const vector<i64>& f2) {
        return f1.size() < f2.size();
    });

    vector<i64> g { 1 };
    for (const auto& fy : v) {
        auto h = convolve(g, fy);
        for (int i = 0; i < (int)h.size(); ++i) cnt[i] += h[i];
        if (g.size() < fy.size()) g.resize(fy.size());
        for (int i = 0; i < (int)fy.size(); ++i) g[i] += fy[i];
    }
    return fx;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    for (int i = 1; i < N; ++i) {
        int x, y; cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
    }
    ctd(0, 1);

    vector<bool> sieve(N, true);
    i64 ans = 0;
    for (int p = 2; p < N; ++p) if (sieve[p]) {
        ans += cnt[p];
        for (int i = 2*p; i < N; i += p) sieve[i] = false;
    }
    cout << setprecision(9) << (2. * (double)ans / N / (N-1));
    return 0;
}
