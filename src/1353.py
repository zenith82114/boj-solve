# Q1353 - Calculus
# Date: 2023.7.30

s, p = map(int, input().split())
if s == p:
    print(1)
    exit(0)
for n in range(2, s+1):
    if s**n >= p * (n**n):
        print(n)
        exit(0)
    if (n+1)**(n+1) > s * (n**n):
        print(-1)
        exit(0)
