/*
 * Q13727 - Berlekamp-Massey alg. + Bostan-Mori alg.
 * Date: 2023.1.29
 */

#include<bits/stdc++.h>
using namespace std;

constexpr int MOD = 1'000'000'007;

struct mint {
    int val;
    mint(): val(0) {}
    mint(int v) {
        val = (-MOD <= v && v < MOD)? v : v % MOD;
        if (val < 0) val += MOD;
    }
    mint(const mint& x): val(x.val) {}

    friend istream& operator>>(istream& is, mint& x) {
        int v; is >> v; x = mint(v); return is;
    }
    friend ostream& operator<<(ostream& os, const mint& x) {
        return os << x.val;
    }
    mint operator-() const { return mint(-val); }
    mint pow(int e) const {
        mint y(1), x(*this);
        for (; e; e >>= 1) { if (e&1) { y *= x; } x *= x; }
        return y;
    }
    mint inv() const { return pow(MOD - 2); }

    bool operator==(const mint& x) const { return val == x.val; }
    bool operator!=(const mint& x) const { return val != x.val; }
    mint operator+(const mint& x) const { return mint(*this) += x; }
    mint& operator+=(const mint& x) {
        if ((val += x.val) >= MOD) val -= MOD;
        return *this;
    }
    mint operator-(const mint& x) const { return mint(*this) -= x; }
    mint& operator-=(const mint& x) {
        if ((val -= x.val) < 0) val += MOD;
        return *this;
    }
    mint operator*(const mint& x) const { return mint(*this) *= x; }
    mint& operator*=(const mint& x) {
        val = (1ll * val * x.val) % MOD; return *this;
    }
    mint operator/(const mint& x) const { return mint(*this) /= x; }
    mint& operator/=(const mint& x) {
        return (*this) *= x.inv();
    }
};

using poly = vector<mint>;

poly poly_mul(poly& A, poly& B) {
    int a = A.size();
    int b = B.size();
    poly C(a + b - 1);
    for (int i = 0; i < a; ++i)
    for (int j = 0; j < b; ++j)
        C[i+j] += A[i] * B[j];
    return C;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<mint> X {
        1, 272, 589185, 930336768, 853401154,
        217676188, 136558333, 415722813, 985269529, 791527976,
        201836136, 382110354, 441223705, 661537677, 641601343,
        897033284, 816519670, 365311407, 300643484, 936803543,
        681929467, 462484986, 13900203, 657627114, 96637209,
        577140657, 600647073, 254604056, 102389682, 811580173,
        592550067, 587171680, 526467503, 265885773, 951722780,
        219627841, 371508152, 283501391, 159234514, 439380999,
        722868959, 125599834, 351398134, 456317548, 365496182,
        614778702, 502680047, 193063685, 309004764, 743901785,
        870955115, 312807829, 160375015, 691844624, 137034372,
        350330868, 895680450, 282610535, 317897557, 28600551,
        583305647, 539409363, 327406961, 627805385, 680183978,
        681299085, 954964592, 743524009, 788048339, 699454626,
        666369521, 857206425, 490463127, 477198247, 599963928,
        21247982, 107843532, 753662937, 239039324, 608530376,
        523383010, 654448101, 801430395, 393034561, 93313778,
        983052766, 240336620, 825539982, 525118275, 563899476,
        706271688, 547405697, 477082486, 664058071, 353207278,
        729486413, 795704637, 999271072, 540749624, 411451016,
        736422999, 879369181, 918733916, 982303557, 512499644,
        261033810, 391766409, 334092786, 931794834, 854181848,
        821090190, 751839258, 433126935, 571194155, 52438113,
        552977155, 320805296, 173355929, 969659468, 258854248,
        159509877, 374487748, 401382023, 44060530, 510164669,
        336596764, 652050424, 373872552, 517226592, 719871041,
        43959496, 235333335, 304962191, 253114421, 43638769,
        361871585, 8060121, 147014624, 114846460, 430864038,
        368951246, 863795701, 36066788, 971606149, 935875286,
        486724123, 73790652, 236936530, 307697424, 753314001
    };
    int N = X.size();

    poly C(N), oldC(N);
    C[0] = 1; oldC[0] = 1;
    mint ld = 1;
    int L = 0;
    int m = 1;

    for (int i = 0; i < N; ++i, ++m) {
        mint d = X[i];
        for (int j = 1; j <= L; ++j)
            d += C[j] * X[i-j];
        if (d == 0) continue;

        poly save(C);
        mint k = d / ld;
        for (int j = m; j < N; ++j)
            C[j] -= k * oldC[j-m];
        if (2*L <= i) {
            L = i+1 - L;
            oldC = save;
            ld = d;
            m = 0;
        }
    }
    C.resize(L+1);
    C.erase(C.begin());
    for (mint& c : C) c = -c;

    poly Q {1};
    for (mint& c : C) Q.emplace_back(-c);
    poly P(X.begin(), X.begin() + L);
    P = poly_mul(P, Q);
    P.resize(L);

    for (cin >> N; N; N >>= 1) {
        poly Qm(Q);
        for (size_t i = 1; i < Qm.size(); i += 2) Qm[i] = -Qm[i];

        P = poly_mul(P, Qm);
        poly P_;
        for (size_t i = N&1; i < P.size(); i += 2) P_.emplace_back(P[i]);
        P = P_;

        Q = poly_mul(Q, Qm);
        poly Q_;
        for (size_t i = 0; i < Q.size(); i += 2) Q_.emplace_back(Q[i]);
        Q = Q_;
    }

    cout << P[0]/Q[0];
    return 0;
}
