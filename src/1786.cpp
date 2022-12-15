/*
 * Q1786 - Knuth-Morris-Pratt alg.
 * Date: 2021.8.15, 2022.10.2(revised)
 */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string T; getline(cin, T);
    int M = T.length();
    string P; getline(cin, P);
    int N = P.length();
    P.push_back('#');

    vector<int> pf(N);
    for (int i = 1, j = 0; i < N; ++i) {
        while (j && P[i] != P[j])
            j = pf[j-1];
        if (P[i] == P[j]) ++j;
        pf[i] = j;
    }

    vector<int> ans;
    for (int i = 0, j = 0; i < M; ++i) {
        while (j && T[i] != P[j])
            j = pf[j-1];
        if (T[i] == P[j]) ++j;
        if (j == N) ans.emplace_back(i -N +1);
    }

    cout << ans.size() << '\n';
    for (const int &a : ans) cout << (a+1) << ' ';
    return 0;
}
