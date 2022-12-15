/*
 * Q14003 - LIS using binary search
 * Date: 2021.8.25, 2022.8.4
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> arr(N), last, pos(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
        auto p = lower_bound(last.begin(), last.end(), arr[i]);
        pos[i] = distance(last.begin(), p);
        if (p != last.end())
            *p = arr[i];
        else
            last.emplace_back(arr[i]);
    }

    cout << last.size() << '\n';
    for (int i = N-1, j = last.size()-1; ~i; --i)
        if (pos[i] == j)
            last[j--] = arr[i];
    for (int& a : last) cout << a << ' ';
    cout << '\n';

    return 0;
}
