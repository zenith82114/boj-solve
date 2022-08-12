/*
 * Q1533 - Vertex splitting
 * Date: 2022.8.12
 */

#include<bits/stdc++.h>
using namespace std;

class Matrix {
    static const int MOD = 1'000'003;
    int N;
public:
    vector<int> arr;
    Matrix(int _N) : arr(_N * _N, 0) {
        N = _N;
    }
    int& operator()(int i, int j) {
        return arr[i * N + j];
    }
    const int& operator()(int i, int j) const {
        return arr[i * N + j];
    }
    Matrix& operator*=(const Matrix& in) {
        Matrix out(N);
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < N; ++k) {
                for (int j = 0; j < N; ++j) {
                    int tmp = (1ll * (*this)(i, k) * in(k, j)) % MOD;
                    out(i, j) = (out(i, j) + tmp) % MOD;
                }
            }
        }
        arr.swap(out.arr);
        return *this;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int data[10][10];

    int N, S, E, T; cin >> N >> S >> E >> T;
    char c;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> c;
            data[i][j] = c - '0';
        }
    }

    int M = 5*N;
    Matrix mat(M);
    for (int i = 0; i < N; ++i) {
        mat(5*i +4, 5*i +3) = 1;
        mat(5*i +3, 5*i +2) = 1;
        mat(5*i +2, 5*i +1) = 1;
        mat(5*i +1, 5*i   ) = 1;

        for (int j = 0; j < N; ++j) if (data[i][j])
            mat(5*i, 5*j + data[i][j] -1) = 1;
    }

    Matrix ans(M);
    for (int i = 0; i < M; ++i)
        ans(i, i) = 1;

    while (T) {
        if (T & 1) ans *= mat;
        T >>= 1; mat *= mat;
    }
    cout << ans(5*(S-1), 5*(E-1)) << endl;
    return 0;
}
