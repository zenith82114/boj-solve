/*
 * Q1046 - geometry
 * Date: 2025.3.15
 */

#include<bits/stdc++.h>
using namespace std;
constexpr double eps = 1e-9;

char a[64][64];
int n, m, is, js;
double xs, ys;
vector<pair<int, double> > slopes;
vector<pair<double, double> > anchors;

void find_anchors(int i, int j, double x, double y, double dx, double dy_dx) {
    if (i < 0 || n <= i || j < 0 || m <= j || a[i][j] == '#') {
        anchors.emplace_back(x, y);
        return;
    }

    int ni = i + (dx < 0? -1 : +1);
    int nj = j + (dx * dy_dx < 0? -1 : +1);
    double nx = i + (dx < 0? 0 : 1);
    double ny = j + (dx * dy_dx < 0? 0 : 1);
    double x_ny = x + (ny - y) / dy_dx;
    double y_nx = y + dy_dx * (nx - x);

    // case 1: to vertical neighbor cell
    if (j + eps < y_nx && y_nx < j + 1 - eps && (x_ny < i - eps || i + 1 + eps < x_ny)) {
        find_anchors(ni, j, nx, y_nx, dx, dy_dx);
    } else
    // case 2: to horizontal neighbor cell
    if (i + eps < x_ny && x_ny < i + 1 - eps && (y_nx < j - eps || j + 1 + eps < y_nx)) {
        find_anchors(i, nj, x_ny, ny, dx, dy_dx);
    } else
    // case 3: through lattice point
    {
        if (dy_dx > 0 && (ni < 0 || n <= ni || a[ni][j] == '#')) anchors.emplace_back(nx, ny);
        if (dy_dx < 0 && (nj < 0 || m <= nj || a[i][nj] == '#')) anchors.emplace_back(nx, ny);
        find_anchors(ni, nj, nx, ny, dx, dy_dx);
        if (dy_dx > 0 && (nj < 0 || m <= nj || a[i][nj] == '#')) anchors.emplace_back(nx, ny);
        if (dy_dx < 0 && (ni < 0 || n <= ni || a[ni][j] == '#')) anchors.emplace_back(nx, ny);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    int walls = 0;

    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
        char& c = a[i][j]; cin >> c;
        if (c == '*') is = i, js = j, xs = i + .5, ys = j + .5;
        else if (c == '#') ++walls;
    }

    for (int x : {0, n})
    for (int y : {0, m}) {
        double dx = x - xs, dy = y - ys;
        slopes.emplace_back(dx < 0? -1 : +1, dy / dx);
    }
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) if (a[i][j] == '#') {
        for (int x : {i, i + 1})
        for (int y : {j, j + 1}) {
            double dx = x - xs, dy = y - ys;
            slopes.emplace_back(dx < 0? -1 : +1, dy / dx);
        }
    }
    sort(slopes.begin(), slopes.end());

    for (const auto& [dx, dy_dx] : slopes) find_anchors(is, js, xs, ys, dx, dy_dx);
    for (auto& [x, y] : anchors) x -= xs, y -= ys;
    anchors.emplace_back(anchors.front());

    double ans = 0.;
    for (auto it = anchors.begin(); next(it) != anchors.end(); ++it) {
        const auto& [x1, y1] = *it;
        const auto& [x2, y2] = *next(it);
        ans += .5 * (x1 * y2 - x2 * y1);
    }
    cout << fixed << setprecision(14) << (n * m - walls - ans);
    return 0;
}
