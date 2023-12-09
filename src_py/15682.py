# Q15682 - Calculus + binary search
# Date: 2023.3.10

import io, os, sys
input = io.BytesIO(os.read(0,os.fstat(0).st_size)).readline
output = sys.stdout.write

from decimal import *

getcontext().prec = 100
L, R = Decimal(-10**6), Decimal(10**6)
TOL = Decimal('.000_000_000_001')

N = int(input())
for _ in range(N):
    a, b, c, d = map(Decimal, input().decode().split())
    if a < 0:
        a, b, c, d = -a, -b, -c, -d
    def eval(x: Decimal) -> Decimal:
        return a*x*x*x + b*x*x + c*x + d

    roots = []

    if b*b == 3*a*c and b*b*b == 27*a*a*d:
        roots.append(-b/(3*a))
    else:
        D = b*b*c*c - 4*a*c*c*c - 4*b*b*b*d - 27*a*a*d*d + 18*a*b*c*d
        if D == 0:
            s = (-b - (b*b - 3*a*c).sqrt()) / (3*a)
            t = (-b + (b*b - 3*a*c).sqrt()) / (3*a)
            if abs(eval(s)) < abs(eval(t)):
                roots.append(s)
                roots.append(-2*s - (b/a))
            else:
                roots.append(-2*t - (b/a))
                roots.append(t)
        elif D < 0:
            l, r = L, R
            while r - l > TOL:
                m = (l + r) / 2
                if eval(m) < 0: l = m
                else: r = m
            roots.append((l + r) / 2)
        else:
            s = (-b - (b*b - 3*a*c).sqrt()) / (3*a)
            t = (-b + (b*b - 3*a*c).sqrt()) / (3*a)
            l, r = L, s
            while r - l > TOL:
                m = (l + r) / 2
                if eval(m) < 0: l = m
                else: r = m
            roots.append((l + r) / 2)
            l, r = s, t
            while r - l > TOL:
                m = (l + r) / 2
                if eval(m) > 0: l = m
                else: r = m
            roots.append((l + r) / 2)
            l, r = t, R
            while r - l > TOL:
                m = (l + r) / 2
                if eval(m) < 0: l = m
                else: r = m
            roots.append((l + r) / 2)

    output(' '.join(map('{:.10f}'.format, roots)) + '\n')
