"""
# Q11930 - minimum enclosing sphere; gradient descent
# Date: 2025.6.14
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from math import hypot as l2norm
    eps = 1e-9
    gamma = .99
    step = .9
    iter = 4096

    n = int(rd())
    p = [tuple(map(int, rd().split())) for _ in range(n)]

    x0, y0, z0 = 0., 0., 0.
    for xi, yi, zi in p:
        x0 += xi
        y0 += yi
        z0 += zi
    x0 /= n
    y0 /= n
    z0 /= n

    for _ in range(iter):
        g, gx, gy, gz = 0., 0., 0., 0.
        for xi, yi, zi in p:
            dx, dy, dz = x0 - xi, y0 - yi, z0 - zi
            d = l2norm(dx, dy, dz)
            if g < d:
                g, gx, gy, gz = d, dx, dy, dz
        if g < eps:
            break
        step *= gamma
        x0 -= step * gx
        y0 -= step * gy
        z0 -= step * gz

    r = max(l2norm(x0 - xi, y0 - yi, z0 - zi) for xi, yi, zi in p)
    print(f"{r:.2f}")


if __name__ == "__main__":
    main()
