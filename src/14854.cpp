/*
 * Q14854 - Lucas's theorem + Chinese remainder theorem
 * Date: 2024.2.26
 */

#include<bits/stdc++.h>
using namespace std;

class CombModPrime {
    int p;
    vector<vector<int> > ar;
public:
    CombModPrime(int P): p(P), ar(P) {
        for (int i = 0; i < p; ++i) {
            ar[i].resize(p, 0);
            ar[i][0] = 1;
            for (int j = 1; j < i; ++j) {
                ar[i][j] = ar[i-1][j-1] + ar[i-1][j];
                if (ar[i][j] >= p) ar[i][j] -= p;
            }
            ar[i][i] = 1;
        }
    }
    int run(int n, int m) {
        int ans = 1;
        while (n > 0 && m > 0) {
            ans = (ans * ar[n%p][m%p]) % p;
            n /= p; m /= p;
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    array<int, 27> fact_wo3;
    fact_wo3[0] = 1;
    for (int i = 1; i < 27; ++i) {
        fact_wo3[i] = ((i%3 == 0? 1 : i) * fact_wo3[i-1]) % 27;
    }

    auto pow_mod27 = [] (int a, int e) {
        int b = 1;
        a %= 27;
        for (; e; e >>= 1) {
            if (e&1) b = b*a%27;
            a = a*a%27;
        }
        return b;
    };

    auto fact_rem3mod27 = [&] (int n) {
        int ans = 1;
        for (; n; n /= 3) {
            ans = (ans * pow_mod27(fact_wo3[26], n/27)) % 27;
            ans = (ans * fact_wo3[n%27]) % 27;
        }
        return ans;
    };

    array<int, 27> inv_mod27;
    for (int i = 0; i < 27; ++i) inv_mod27[i] = pow_mod27(i, 17);

    auto count_3 = [] (int n) {
        int ans = 0;
        for (; n; n /= 3) ans += n/3;
        return ans;
    };

    auto comb_mod27 = [&] (int n, int m) {
        int e = count_3(n) - count_3(m) - count_3(n-m);
        if (e >= 3) return 0;
        int ans = 1;
        while (e--) ans *= 3;
        ans = (ans * fact_rem3mod27(n)) % 27;
        ans = (ans * inv_mod27[fact_rem3mod27(m)]) % 27;
        ans = (ans * inv_mod27[fact_rem3mod27(n-m)]) % 27;
        return ans;
    };

    CombModPrime cmod11(11), cmod13(13), cmod37(37);

    int tc; cin >> tc; while (tc--) {
        int n, m; cin >> n >> m;
        int a27 = comb_mod27(n, m);
        int a11 = cmod11.run(n, m);
        int a13 = cmod13.run(n, m);
        int a37 = cmod37.run(n, m);
        int ans = (a27*137566 + a11*103896 + a13*109890 + a37*77220) % 142857;
        cout << ans << '\n';
    }

    return 0;
}
