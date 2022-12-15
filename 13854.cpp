/*
 * Q13854 - Centroid DnC + FFT
 * Date: 2022.2.22
 */

#include<bits/stdc++.h>
using namespace std;
using cpx = complex<double>;
using ll = long long;
const int MAXN = 50000;
const double PI = acos(-1);

vector<int> adj[MAXN+1];
int sz[MAXN+1];
bool sel[MAXN+1]={false};

uint bitrev(uint x, uint b) {
    x = ((x & 0xaaaaaaaa)>>1) | ((x & 0x55555555)<<1);
    x = ((x & 0xcccccccc)>>2) | ((x & 0x33333333)<<2);
    x = ((x & 0xf0f0f0f0)>>4) | ((x & 0x0f0f0f0f)<<4);
    x = ((x & 0xff00ff00)>>8) | ((x & 0x00ff00ff)<<8);
    x = (x>>16) | (x<<16);
    return x>>(32-b);
}
void fft(vector<cpx>& A, bool inv) {
    int N = (int)A.size();
    uint lgN = (uint)log2(N);
    double theta;
    cpx a, b, z, w;
    for (int i = 0, j; i < N; ++i) {
        j = bitrev(i, lgN);
        if (i < j)
            swap(A[i], A[j]);
    }
    for (int n = 1; n < N; n <<= 1) {
        theta = inv ? -PI/(double)n : PI/(double)n;
        for (int m = 0; m < N; m += n<<1) {
            z = 1.0;
            w = polar(1.0, theta);
            for (int i = 0, j = n; i < n; ++i, ++j) {
                a = A[m+i];
                b = A[m+j] * z;
                A[m+i] = a+b;
                A[m+j] = a-b;
                z *= w;
            }
        }
    }
    if (inv) {
        for (auto& a : A)
            a /= (double)N;
    }
}

int dfs(int pu, int u, int d, vector<cpx>& vd) {
    vd[d] += 1.0;
    sz[u] = 1;
    for (int& v : adj[u])
        if (v != pu && !sel[v])
            sz[u] += dfs(u, v, d+1, vd);
    return sz[u];
}
int ct(int pu, int u, int m) {
    bool done = false;
    while (!done) {
        done = true;
        for (int& v : adj[u]) {
            if (v != pu && !sel[v] && sz[v] > m) {
                pu = u, u = v;
                done = false;
                break;
            }
        }
    }
    return u;
}
int ceil_pow2(int n) {
    if (n & (n-1)) {
        for (int i = 1; i < 32; i <<= 1)
            n |= (n>>i);
        return n+1;
    }
    return n;
}
void ctd(int pc, int u, vector<cpx>& vd, vector<int>& vl) {
    int n = dfs(pc, u, 1, vd);
    int c = ct(pc, u, n>>1);
    sel[c] = true;

    vector<int> vv;
    // vector<cpx> tvl;
    // vector<vector<cpx>> vvd;
    // vector<vector<int>> vvl;
    for (int& v : adj[c]) if (!sel[v])
        vv.emplace_back(v);
    int nv = (int)vv.size();
    if (nv) {
        int K = ceil_pow2(n);
        vector<cpx> tvl(K);
        vector<vector<cpx>> vvd(nv, vector<cpx>(K, 0.0));
        vector<vector<int>> vvl(nv, vector<int>(K, 0));
        for (int i = 0; i < nv; ++i)
            ctd(c, vv[i], vvd[i], vvl[i]);

        // paths one of whose endpoints is the centroid
        for (int i = 0; i < nv; ++i)
            for (int k = 0; k < K; ++k)
                vl[k] += (int)round(vvd[i][k].real());

        // paths whose endpoints belong to different subtrees
        if (nv > 1) {
            for (int i = 0; i < nv; ++i)
                fft(vvd[i], false);
            for (int i = 0; i < nv; ++i) {
                for (int j = i+1; j < nv; ++j) {
                    for (int k = 0; k < K; ++k)
                        tvl[k] = vvd[i][k] * vvd[j][k];
                    fft(tvl, true);
                    for (int k = 0; k < K; ++k)
                        vl[k] += (int)round(tvl[k].real());
                }
            }
        }

        // paths whose endpoints belong to same subtree
        for (int i = 0; i < nv; ++i)
            for (int k = 0; k < K; ++k)
                vl[k] += vvl[i][k];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    for (int n = 1; n < N; ++n) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<cpx> vd(ceil_pow2(N), 0.0);
    vector<int> vl(vd.size(), 0);
    ctd(0, 1, vd, vl);

    vector<bool> prime(N, true);
    ll C = ((ll)N*(N-1))>>1;
    ll pC = 0;
    for (ll p = 2; p < N; ++p) {
        if (prime[p]) {
            pC += vl[p];
            for (ll q = p*p; q < N; q += p)
                prime[q] = false;
        }
    }

    cout << (double)pC/C << '\n';
    return 0;
}
