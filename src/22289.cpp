/*
 * Q22289 - FFT
 * Date: 2024.11.4
 */

#include<bits/stdc++.h>
using namespace std;

using cpx = complex<double>;
const double PI = acos(-1.);

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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    constexpr int D = 4;
    constexpr int pw10D = 10000;

    string a, b; cin >> a >> b;
    if (a[0] == '0' || b[0] == '0') { cout << 0; return 0; }

    vector<cpx> A, B;
    int x = 0, m = 1, d = 0;
    while (!a.empty()) {
        x += m * (a.back() - '0'); a.pop_back();
        m *= 10;
        if (++d == D) {
            A.emplace_back(x);
            x = 0, m = 1, d = 0;
        }
    }
    if (x) A.emplace_back(x);
    x = 0, m = 1, d = 0;
    while (!b.empty()) {
        x += m * (b.back() - '0'); b.pop_back();
        m *= 10;
        if (++d == D) {
            B.emplace_back(x);
            x = 0, m = 1, d = 0;
        }
    }
    if (x) B.emplace_back(x);

    int na = A.size(), nb = B.size();
    int n = 1; while (n < na + nb - 1) n <<= 1;
    A.resize(n); B.resize(n);
    fft(A); fft(B);
    for (int i = 0; i < n; ++i) A[i] *= B[i];
    fft(A, true);

    vector<int> ans;
    int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += llround(A[i].real());
        ans.push_back(sum % pw10D);
        sum /= pw10D;
    }
    for (; sum; sum /= pw10D) ans.push_back(sum % pw10D);
    while (ans.back() == 0) ans.pop_back();
    cout << setfill('0');
    while (!ans.empty()) {
        cout << ans.back();
        ans.pop_back();
        cout << setw(D);
    }
    return 0;
}
