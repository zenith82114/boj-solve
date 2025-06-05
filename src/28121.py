"""
# Q28121 - disjoint sets
# Date: 2025.6.4
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, q = map(int, rd().split())
    uf = [-1] * (2*n + 1)
    pt = [int(i > n) for i in range(2*n + 1)]
    ans = 0

    def find(x):
        if uf[x] < 0: return x
        uf[x] = find(uf[x])
        return uf[x]

    def neg(x):
        return 2*n + 1 - x

    def unite(x, y):
        nonlocal ans
        x, y = find(x), find(y)
        if x == y: return
        if uf[x] < uf[y]: x, y = y, x
        if x == find(neg(x)): ans -= pt[x]
        if y == find(neg(y)): ans -= pt[y]
        uf[y] += uf[x]
        uf[x] = y
        pt[y] += pt[x]
        if y == find(neg(y)): ans += pt[y]

    for _ in range(q):
        x, y = map(int, rd().split())
        unite(x, neg(y))
        unite(y, neg(x))
        print(ans)


if __name__ == "__main__":
    main()
