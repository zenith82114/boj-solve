/*
 * Q3878 - Separating two groups of points w/ convex hull
 * Date: 2022.1.22
 */

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct vec2 {
    int x, y;
    bool operator<(const vec2& v) const {
        return y != v.y ? y < v.y : x < v.x;
    };
    vec2 operator-(const vec2& v) const {
        return { x-v.x, y-v.y };
    }
};
int64_t cross(const vec2& v, const vec2& w) {
    return v.x*w.y - v.y*w.x;
}
int64_t dot(const vec2& v, const vec2& w) {
    return v.x*w.x + v.y*w.y;
}
int ccw(const vec2& o, const vec2& p, const vec2& q) {
    auto k = cross(p-o, q-o);
    return (k < 0) ? -1 : (k > 0);
}
bool intersects(vec2 a, vec2 b, vec2 c, vec2 d) {
    int ab = ccw(a,b,c) * ccw(a,b,d);
    int cd = ccw(c,d,a) * ccw(c,d,b);
    if (!(ab || cd)) {
        if (b < a) swap(a,b);
        if (d < c) swap(c,d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

vec2 orig;
bool polarSort(const vec2& p, const vec2& q) {
    int k = ccw(orig,p,q);
    return k != 0 ? k > 0 : dot(q-p, orig-p) < 0;
}
void getConvexHull(vector<vec2>& G, vector<vec2>& H) {
    int N = G.size();
    int M = 0;
    for (int n = 0; n < N; n++) {
        if (G[n] < G[M])
            M = n;
    }
    swap(G.front(), G[M]);
    orig = G.front();
    sort(++G.begin(), G.end(), polarSort);

    H.clear();
    M = 0;
    for (auto &p : G) {
        while (M > 1 && ccw(H[M-2], H[M-1], p) <= 0) {
            H.pop_back();
            M--;
        }
        H.push_back(p);
        M++;
    }
}

bool separable(vector<vec2>& H1, vector<vec2>& H2) {
    int M1 = H1.size(), M2 = H2.size();
    int i, j;
    bool b1 = false, b2 = false;
    if (M1 < M2) {
        swap(M1, M2);
        swap(H1, H2);
    }
    if (M2 > 1) {
        for (i = 0; i < M1; i++) {
            for (j = 0; j < M2; j++) {
                if (intersects(H1[i], H1[(i+1)%M1], H2[j], H2[(j+1)%M2]))
                    return false;
            }
        }
        if (M1 > 2) {
            for (i = 0; !b1 && i < M1; i++) {
                for (j = 0; j < M2; j++) {
                    if (ccw(H1[i], H1[(i+1)%M1], H2[j]) <= 0) {
                        b1 = true; break;
                    }
                }
            }
        }
        if (M2 > 2) {
            for (j = 0; !b2 && j < M2; j++) {
                for (i = 0; i < M1; i++) {
                    if (ccw(H2[j], H2[(j+1)%M2], H1[i]) <= 0) {
                        b2 = true; break;
                    }
                }
            }
        }
        if (b1 != b2)
            return false;
    }
    else if (M1 > 1) {
        for (i = 0; i < M1; i++) {
            auto k = ccw(H1[i], H1[(i+1)%M1], H2[0]);
            if (k < 0)
                return true;
            if (k == 0 && dot(H1[i]-H2[0], H1[(i+1)%M1]-H2[0]) <= 0)
                return false;
        }
    }
    return true;
}

vector<vec2> G1, G2, H1, H2;
int TC, N1, N2;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> TC;
    while (TC--) {
        cin >> N1 >> N2;
        G1.resize(N1);
        for (int n = 0; n < N1; n++)
            cin >> G1[n].x >> G1[n].y;
        getConvexHull(G1, H1);
        G2.resize(N2);
        for (int n = 0; n < N2; n++)
            cin >> G2[n].x >> G2[n].y;
        getConvexHull(G2, H2);

        cout << (separable(H1, H2) ? "YES\n" : "NO\n");
    }

    return 0;
}
