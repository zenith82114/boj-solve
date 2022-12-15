/*
 * Q4149 - Miller-Rabin primality test and Pollard's rho alg.
 * Date: 2022.2.2
 */

#include<bits/stdc++.h>
using namespace std;

ulong mul_mod(const ulong A, const ulong B, const ulong p) {
    ulong a = A%p;
    ulong b = B%p;
    ulong r = b&1 ? a : 0;
    while (b >>= 1) {
        a = (a<<1) % p;
        if (b&1)
            r = (a+r) % p;
    }
    return r;
}
ulong pow_mod(const ulong A, const ulong B, const ulong p) {
    ulong a = A%p;
    ulong b = B;
    ulong r = b&1 ? a : 1;
    while (b >>= 1) {
        a = mul_mod(a, a, p);
        if (b&1)
            r = mul_mod(a, r, p);
    }
    return r;
}
default_random_engine gen;
bool probable_prime(const ulong p, const ulong q, const ulong r,
uniform_int_distribution<ulong>& dist) {
    ulong x, y;
    x = dist(gen);
    y = pow_mod(x, q, p);
    if (y == 1)
        return true;
    for (ulong i = 0; i < r; ++i) {
        if (y == p-1)
            return true;
        y = mul_mod(y, y, p);
        if (y == 1)
            return false;
    }
    return false;
}
constexpr int trial = 20;
bool miller_rabin(ulong p) {
    uniform_int_distribution<ulong> dist(2, p-1);
    ulong q = p-1, r = 0;
        while (!(q&1)) {
        q >>= 1;
        r++;
    }
    for (int i = 0; i < trial; ++i) {
        if (!probable_prime(p, q, r, dist))
            return false;
    }
    return true;
}

inline ulong diff(ulong x, ulong y) {
    return x>y ? x-y : y-x;
}
inline ulong G(ulong x, ulong N) {
    return (mul_mod(x, x, N)+1)%N;
}
ulong gcd(ulong a, ulong b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
void factorize(ulong N, vector<ulong>& v) {
    if (miller_rabin(N)) {
        v.push_back(N);
        return;
    }
    // Pollard rho
    ulong p;
    for (ulong i = 1; i <= N; ++i) {
        ulong x = i, y = i;
        p = 1;
        while (p == 1) {
            x = G(x, N);
            y = G(G(y, N), N);
            p = gcd(N, diff(x, y));
        }
        if (p != N)
            break;
    }
    // success: recurse
    if (p != N) {
        factorize(p, v);
        factorize(N/p, v);
    }
    // failure: bruteforce
    else {
        for (p = 3; p*p <= N; p += 2) {
            if (N%p == 0) {
                v.push_back(p);
                factorize(N/p, v);
                return;
            }
        }
        // here N is prime
        v.push_back(N);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ulong N; cin >> N;
    vector<ulong> v;
    while (!(N&1)) {
        N >>= 1;
        v.push_back(2);
    }
    if (N > 1) factorize(N, v);
    sort(v.begin(), v.end());
    for (auto& p : v) cout << p << '\n';
    return 0;
}
