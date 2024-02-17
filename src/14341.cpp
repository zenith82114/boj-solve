/*
 * Q14341 - Probability theory, DP
 * Date: 2024.2.18
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    constexpr int MAXN = 10'000'000;
    constexpr int MOD  = 1'000'000'007;
    auto add_mod = [] (int x, int y) { return (x+y)%MOD; };
    auto sub_mod = [] (int x, int y) { return (MOD+x-y)%MOD; };
    auto mul_mod = [] (int x, int y) { return (int)(((int64_t)x*y)%MOD); };
    auto div_mod = [&mul_mod] (int x, int y) {
        for (int e = MOD-2; e; e >>= 1) {
            if (e&1) x = mul_mod(x, y);
            y = mul_mod(y, y);
        }
        return x;
    };

    vector<int> f(MAXN+1);
    f[MAXN] = 1;
    for (int i = 2; i < MAXN; ++i) {
        f[MAXN] = mul_mod(f[MAXN], i);
    }
    f[MAXN] = div_mod(1, f[MAXN]);
    for (int i = MAXN; i; --i) {
        f[i-1] = mul_mod(f[i], i-1);
    }
    for (int i = 1; i <= MAXN; ++i) {
        f[i] = (i&1? add_mod : sub_mod)(f[i-1], f[i]);
    }

    int tc; cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        int n, k; cin >> n >> k;
        int ans = sub_mod(1, mul_mod(f[k], f[n-k+1]));
        cout << "Case #"<<i<<": "<<ans << '\n';
    }

    return 0;
}
