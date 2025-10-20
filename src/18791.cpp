/*
 * Q18791 - Erdos-Ginzburg-Ziv theorem
 * Date: 2025.10.21
 */

#include<bits/stdc++.h>
using namespace std;
using i64 = int64_t;

int spf[5004];
int opt[5000][5000];

vector<int> solve(vector<int>& arr) {
    const int n = (arr.size() + 1) / 2;
    assert(n > 1);

    if (spf[n] == n) {
        vector<int> cnt(n, 0);
        for (int x : arr) ++cnt[x];
        priority_queue<pair<int, int> > pq;
        for (int x = 0; x < n; ++x) if (cnt[x]) pq.emplace(cnt[x], x);

        auto [cx0, x0] = pq.top(); pq.pop();
        if (cx0 >= n) {
            cnt[x0] -= n;
            arr.clear();
            for (int x = 0; x < n; ++x) while (cnt[x]--) arr.emplace_back(x);
            vector<int> ans(n, x0);

            return ans;
        }

        vector<int> t[2]; t[0].emplace_back(x0); t[1].emplace_back(x0);
        if (--cx0) pq.emplace(cx0, x0);
        while (!pq.empty()) {
            auto [cx, x] = pq.top(); pq.pop();
            assert(!pq.empty());
            auto [cy, y] = pq.top(); pq.pop();
            assert(x != y);
            t[0].emplace_back(x); if (--cx) pq.emplace(cx, x);
            t[1].emplace_back(y); if (--cy) pq.emplace(cy, y);
        }
        assert((int)t[0].size() == n);
        assert((int)t[1].size() == n);

        fill_n(opt[0], n, -1);
        opt[0][x0] = 0;
        for (int i = 1; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            opt[i][j] = -1;
            for (int k : {0, 1}) {
                int jj = (j + n - t[k][i]) % n;
                if (opt[i - 1][jj] > -1) opt[i][j] = k;
            }
        }
        assert(opt[n - 1][0] > -1);

        vector<int> ans;
        for (int i = n - 1, j = 0; i >= 0; --i) {
            int x = t[opt[i][j]][i];
            ans.emplace_back(x);
            --cnt[x];
            j = (j + n - x) % n;
        }
        arr.clear();
        for (int x = 0; x < n; ++x) while (cnt[x]--) arr.emplace_back(x);

        return ans;
    }
    else {
        const int a = spf[n], b = n/a;
        vector<vector<int> > arr_mod(a);
        for (int& x : arr) {
            arr_mod[x % a].emplace_back(x);
            x %= a;
        }

        vector<vector<int> > groups;
        vector<int> next_arr;
        while ((int)groups.size() < 2*b - 1) {
            while ((int)next_arr.size() < 2*a - 1) {
                next_arr.emplace_back(arr.back());
                arr.pop_back();
            }
            vector<int> new_group;
            for (int x : solve(next_arr)) {
                new_group.emplace_back(arr_mod[x].back());
                arr_mod[x].pop_back();
            }
            groups.emplace_back(new_group);
        }

        vector<vector<int> > gsum_to_gid(b);
        next_arr.clear();
        for (int i = 0; i < 2*b - 1; ++i) {
            int gsum = accumulate(begin(groups[i]), end(groups[i]), 0);
            assert(gsum % a == 0);
            gsum /= a;
            gsum_to_gid[gsum % b].emplace_back(i);
            next_arr.emplace_back(gsum % b);
        }

        vector<int> ans;
        for (int gsum : solve(next_arr)) {
            int i = gsum_to_gid[gsum].back(); gsum_to_gid[gsum].pop_back();
            ans.insert(end(ans), begin(groups[i]), end(groups[i]));
        }
        arr.clear();
        for (auto& u : arr_mod) arr.insert(end(arr), begin(u), end(u));

        return ans;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    iota(spf, spf + 5001, 0);
    for (int i = 2; i <= 5000; ++i) if (spf[i] == i) {
        for (int j = i*i; j <= 5000; j += i) spf[j] = min(spf[j], i);
    }

    int n; cin >> n;
    vector<int> arr(2*n - 1); for (int& x : arr) cin >> x;
    if (n == 1) { cout << arr[0]; return 0; }
    for (int x : solve(arr)) cout << x << ' ';
    return 0;
}
