/*
 * Q12022 - Stable marriage problem
 * Date: 2023.6.23
 */

#include<bits/stdc++.h>
using namespace std;

int x_list[1024][1024];
int y_rlist[1024][1024];
int x_ptr[1024];
int mx[1024], my[1024];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N; cin >> N;
    for (int x = 1; x <= N; ++x)
    for (int i = 0; i < N; ++i)
        cin >> x_list[x][i];

    for (int y = 1; y <= N; ++y)
    for (int i = 0; i < N; ++i) {
        int x; cin >> x; y_rlist[y][x] = i;
    }

    queue<int> q;
    for (int x = 1; x <= N; ++x) q.emplace(x);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        int y = x_list[x][x_ptr[x]++];
        int z = my[y];
        if (z) {
            if (y_rlist[y][x] < y_rlist[y][z]) {
                mx[z] = 0;
                q.emplace(z);
                mx[x] = y;
                my[y] = x;
            }
            else q.emplace(x);
        }
        else {
            mx[x] = y;
            my[y] = x;
        }
    }

    for (int x = 1; x <= N; ++x) cout << mx[x] << '\n';
    return 0;
}
