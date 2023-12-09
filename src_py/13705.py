# Q13705 - Calculus + binary search
# Date: 2023.3.12

from decimal import *
getcontext().prec = 100

def sin(x: Decimal) -> Decimal:
    x %= Decimal('6.28318_53071_79586_47692_52867_66559_00576_83943_38798_75021_'
                   '16419_49889_18461_56328_12572_41799_72560_69650_68423_4136')
    t = x
    y = x
    for n in range(2, 50, 2):
        t = -t
        t /= Decimal(n * (n+1))
        t *= x*x
        y += t
    return y

a, b, c = map(Decimal, input().split())
l, r = Decimal(0), Decimal(10**6)
while r - l > Decimal('.00000_00000_00000_00000_00000_00000_00000_00000_00001'):
    m = (l + r) / 2
    if a*m + b*sin(m) < c: l = m
    else: r = m
print('{:.6f}'.format(l))
