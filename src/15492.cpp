/*
 * Q15492 - minimal string rotation; Booth's alg.
 * Date: 2025.6.23
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int a[4'000'000], f[8'000'000];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    for (int i = n - 1; i > -1; --i) cin >> a[i];
    memset(f, -1, 2*n * sizeof(int));
    /* run j = 1 separately and skip k = 0 */
    if (a[1] == a[0]) f[1] = 0;
    int k = 1;

    /* skip updates of k to 0 or to n */
    for (int j = 2; j < 2*n; ++j) {
        int i = f[j - k - 1];
        while (i != -1 && a[j % n] != a[(k + i + 1) % n]) {
            if (a[j % n] < a[(k + i + 1) % n]
            && j - i - 1 != 0 && j - i - 1 != n) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (i == -1 && a[j % n] != a[(k + i + 1) % n]) {
            if (a[j % n] < a[(k + i + 1) % n] && j != n) {
                k = j;
            }
            f[j - k] = -1;
        }
        else f[j - k] = i + 1;
    }

    for (int i = k; i < n; ++i) cout << a[i] << ' ';
    for (int i = 0; i < k; ++i) cout << a[i] << ' ';
    return 0;
}
