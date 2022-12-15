/*
 * Q15576 - FFT
 * Date: 2022.2.4
 */

#include<bits/stdc++.h>
using namespace std;
using cpx = complex<double>;
const double PI = acos(-1);
const uint lgD = 20, D = 1<<lgD;

uint bitrev32(uint x) {
    x = ((x & 0xaaaaaaaa)>>1) | ((x & 0x55555555)<<1);
    x = ((x & 0xcccccccc)>>2) | ((x & 0x33333333)<<2);
    x = ((x & 0xf0f0f0f0)>>4) | ((x & 0x0f0f0f0f)<<4);
    x = ((x & 0xff00ff00)>>8) | ((x & 0x00ff00ff)<<8);
    x = (x>>16) | (x<<16);
    return x>>(32-lgD);
}

void fft(vector<cpx>& P, const bool inv) {
    double theta;
    cpx a, b, z, w;
    for (uint i = 0, j; i < D; i++) {
        j = bitrev32(i);
        if (i < j)
            swap(P[i], P[j]);
    }
    for (uint n = 1; n < D; n <<= 1) {
        theta = inv ? -PI/(double)n : PI/(double)n;
        for (uint m = 0; m < D; m += n<<1) {
            z = 1.0;
            w = polar(1.0, theta);
            for (uint i = 0, j = n; i < n; ++i, ++j) {
                a = P[m+i];
                b = P[m+j] * z;
                P[m+i] = a+b;
                P[m+j] = a-b;
                z *= w;
            }
        }
    }
    if (inv) {
        for (auto& p : P)
            p /= (double)D;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string A, B; cin >> A >> B;
    if (A == "0" || B == "0") {
        cout << "0\n";
        return 0;
    }

    vector<cpx> PA, PB;
    for (auto a = A.rbegin(); a != A.rend(); a++)
        PA.push_back(*a - '0');
    PA.resize(D);
    for (auto b = B.rbegin(); b != B.rend(); b++)
        PB.push_back(*b - '0');
    PB.resize(D);

    fft(PA, false);
    fft(PB, false);
    for (uint i = 0; i < D; ++i)
        PA[i] *= PB[i];
    fft(PA, true);

    uint d = A.length() + B.length();
    string X; X.resize(d);
    int c = 0;
    for (uint i = 0; i < d; ++i) {
        int v = (int)round(PA[i].real());
        v += c;
        X[d-1-i] = '0' + (v%10);
        c = v/10;
    }
    if (X[0] == '0')
        X.erase(0, 1);
    cout << X << '\n';

    return 0;
}
