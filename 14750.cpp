/*
 * Q14750 - Line segment intersection + Bipartite matching
 * Date: 2022.1.27
 */

#include<iostream>
#include<algorithm>
#include<array>
#include<queue>
#include<vector>
using namespace std;

struct vec2 {
    int64_t x, y;
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
bool contains(const vec2& a, const vec2& b, const vec2& c) {
    auto k = cross(b-a, c-a);
    return (k != 0) ? false : (dot(a-c, b-c) <= 0);
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

array<array<int, 302>, 302> G{};
array<bool, 302> visited;
array<int, 302> pred;

bool bfs(const int S, const int T) {
    queue<int> q;
    int u, v;
    q.push(S);
    visited.fill(false);
    visited[S] = true;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (v = 0; v <= T; v++) {
            if (!visited[v] && G[u][v] > 0) {
                if (v == T) {
                    pred[T] = u;
                    return true;
                }
                visited[v] = true;
                pred[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<vec2> corners, holes, mice;
    bool flag;
    int N, K, H, M, n, h, m;
    int S, T, C;

    cin >> N >> K >> H >> M;
    corners.resize(N);
    holes.resize(H);
    mice.resize(M);
    for (n = 0; n < N; n++)
        cin >> corners[n].x >> corners[n].y;
    for (h = 0; h < H; h++)
        cin >> holes[h].x >> holes[h].y;
    for (m = 0; m < M; m++)
        cin >> mice[m].x >> mice[m].y;

    S = M+H;
    T = S+1;
    for (m = 0; m < M; m++) {
        for (h = 0; h < H; h++) {
            flag = true;
            for (n = 0; n < N; n++) {
                if (!contains(corners[n], corners[(n+1)%N], holes[h]) &&
                    intersects(corners[n], corners[(n+1)%N], mice[m], holes[h])) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                G[m][M+h] = 1;
        }
    }
    for (m = 0; m < M; m++)
        G[S][m] = 1;
    for (h = 0; h < H; h++)
        G[M+h][T] = K;

    C = 0;
    while (bfs(S, T)) {
        C++;
        for (int v = T; v != S; v = pred[v]) {
            G[pred[v]][v]--;
            G[v][pred[v]]++;
        }
    }

    cout << (C == M ? "Possible\n" : "Impossible\n");
    return 0;
}
