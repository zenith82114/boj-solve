# Q31397 - Geometry, binary search
# Date: 2024.6.18

import sys
rd = sys.stdin.readline
from math import sqrt

def dist(a, b) -> float:
    return sqrt((a[0] - b[0])**2 + (a[1] - b[1])**2)

def area(a, b, c) -> float:
    x1, y1 = b[0] - a[0], b[1] - a[1]
    x2, y2 = c[0] - a[0], c[1] - a[1]
    return 0.5*(x1*y2 - x2*y1)

def lerp(a, b, t) -> tuple:
    return (
        t*b[0] + (1-t)*a[0],
        t*b[1] + (1-t)*a[1],
    )

def main() -> None:
    n = int(rd())
    v = []
    for _ in range(n):
        x, y = map(int, rd().split())
        v.append((x, y))
    v.append(v[0])

    d = [dist(v[i], v[i+1]) for i in range(n)]
    L = sum(d)
    A = sum(area(v[0], v[i], v[i+1]) for i in range(n))

    def walk(p, ip, tp, l):
        ll = (1 - tp) * d[ip]
        if l < ll:
            q = lerp(p, v[ip+1], l / ll)
            iq = ip
            tq = dist(v[ip], q) / d[ip]
            return q, iq, tq
        for i in range(ip+1, n):
            if l < ll + d[i]:
                tq = (l - ll) / d[i]
                q = lerp(v[i], v[i+1], tq)
                iq = i
                return q, iq, tq
            ll += d[i]

    def eval_f(p, ip, tp):
        q, iq, _ = walk(p, ip, tp, L / 2)
        a = 0.
        for i in range(ip+1, iq):
            a += area(p, v[i], v[i+1])
        a += area(p, v[iq], q)
        return 2*a < A

    p, ip, tp, l = v[0], 0, 0., L / 2
    fp = eval_f(p, ip, tp)

    while l > 1e-9:
        l /= 2
        m, im, tm = walk(p, ip, tp, l)
        if eval_f(m, im, tm) == fp:
            p, ip, tp = m, im, tm

    _, iq, tq = walk(p, ip, tp, L / 2)
    print("YES")
    print(ip+1, f"{tp:.12f}")
    print(iq+1, f"{tq:.12f}")

if __name__ == "__main__":
    main()
