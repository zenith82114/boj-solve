/*
 * Q1786 - KMP matching
 * Date: 2021.8.15
 */

#include<iostream>
#include<string>
#include<vector>
using namespace std;

constexpr int maxN = 1000000, maxM = 1000000;
int border[maxM + 1] = { 0 };

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    string T, P;
    int N, M, i, j;
    vector<int> matches;

    getline(cin, T); N = T.length();
    getline(cin, P); M = P.length();

    j = 0;
    for (i = 1; i <= M; ++i) {
        while (j && P[j] != P[i])
            j = border[j];
        if (P[j] == P[i]) j++;
        border[i + 1] = j;
    }
    j = 0;
    for (i = 0; i <= N; ++i) {
        while (j && P[j] != T[i])
            j = border[j];
        if (P[j] == T[i]) j++;
        if (j == M) {
            matches.push_back(i - M + 2);
            j = border[j];
        }
    }
    cout << matches.size() << '\n';
    for (int& m : matches) cout << m << ' ';

    return 0;
}