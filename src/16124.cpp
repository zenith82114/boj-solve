/*
 * Q16124 - Lazy segment tree
 * Date: 2024.3.1
 */

#include<bits/stdc++.h>
using namespace std;

class LazySegTree {
    constexpr static int MOD = 998'244'353;
    int n, lgn;
    vector<int> pw10, wei;
    vector<array<int, 10> > ar, lz;

    int add_mod(int a, int b) { return (a+b)%MOD; }
    int mul_mod(int a, int b) { return (int64_t)a*b%MOD; }

    void apply(int i, const array<int, 10>& f) {
        array<int, 10> temp; temp.fill(0);
        for (int x = 0; x < 10; ++x) {
            temp[f[x]] = add_mod(temp[f[x]], ar[i][x]);
        }
        copy(temp.begin(), temp.end(), ar[i].begin());
        if (~i & n) {
            for (int x = 0; x < 10; ++x) {
                temp[x] = f[lz[i][x]];
            }
            copy(temp.begin(), temp.end(), lz[i].begin());
        }
    }
    void push(int i) {
        apply(i<<1, lz[i]);
        apply(i<<1|1, lz[i]);
        iota(lz[i].begin(), lz[i].end(), 0);
    }
    void pull(int i) {
        int p = pw10[wei[i<<1] - wei[i<<1|1]];
        for (int x = 0; x < 10; ++x) {
            ar[i][x] = add_mod(mul_mod(p, ar[i<<1][x]), ar[i<<1|1][x]);
        }
    }

public:
    LazySegTree(const string& str) {
        int sz = str.size();
        for (n = 1, lgn = 0; n < sz; n <<= 1, ++lgn);

        pw10.resize(sz); pw10[0] = 1;
        for (int i = 1; i < sz; ++i) pw10[i] = mul_mod(10, pw10[i-1]);

        ar.resize(n<<1);
        wei.resize(n<<1);
        for (int i = 0; i < n; ++i) ar[n|i].fill(0);
        for (int i = 0; i < sz; ++i) {
            ar[n|i][str[i]-'0'] = 1;
            wei[n|i] = sz-1-i;
        }
        for (int i = n-1; i > 0; --i) {
            pull(i);
            wei[i] = wei[i<<1|1];
        }

        lz.resize(n);
        for (int i = 1; i < n; ++i) iota(lz[i].begin(), lz[i].end(), 0);
    }
    void update(int i, int j, const array<int, 10>& f) {
        i |= n, j |= n;
        for (int k = lgn; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }
        for (int l = i, r = j; l <= r; l >>= 1, r >>= 1) {
            if ( l&1) apply(l++, f);
            if (~r&1) apply(r--, f);
        }
        for (int k = 1; k <= lgn; ++k) {
            if (    i>>k<<k !=   i) pull(i>>k);
            if ((j+1)>>k<<k != j+1) pull(j>>k);
        }
    }
    int query(int i, int j) {
        i |= n, j |= n;
        for (int k = lgn; k; --k) {
            if (    i>>k<<k !=   i) push(i>>k);
            if ((j+1)>>k<<k != j+1) push(j>>k);
        }

        array<int, 10> acc; acc.fill(0);
        int w0 = wei[j];
        for (; i <= j; i >>= 1, j >>= 1) {
            if ( i&1) {
                for (int x = 0; x < 10; ++x) {
                    acc[x] = add_mod(
                        acc[x], mul_mod(pw10[wei[i] - w0], ar[i][x])
                    );
                }
                ++i;
            }
            if (~j&1) {
                for (int x = 0; x < 10; ++x) {
                    acc[x] = add_mod(
                        acc[x], mul_mod(pw10[wei[j] - w0], ar[j][x])
                    );
                }
                --j;
            }
        }

        int ans = 0;
        for (int x = 0; x < 10; ++x) ans = add_mod(ans, mul_mod(x, acc[x]));
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string str; cin >> str;
    LazySegTree segt(str);

    array<int, 10> f;
    iota(f.begin(), f.end(), 0);

    int q; cin >> q;
    while (q--) {
        int op, i, j, x, y; cin >> op >> i >> j;
        --i; --j;
        if (op&1) {
            cin >> x >> y;
            f[x] = y;
            segt.update(i, j, f);
            f[x] = x;
        } else {
            cout << segt.query(i, j) << '\n';
        }
    }

    return 0;
}
