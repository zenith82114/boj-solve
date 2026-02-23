"""
# Q13005 - dfs, greedy
# Date: 2026.2.23
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    sys.setrecursionlimit(101010)

    n = int(rd())
    a = [0]; a.extend(map(int, rd().split()))
    g = [[] for _ in range(n + 1)]
    for x in range(2, n + 1):
        y, w = map(int, rd().split())
        g[x].append((y, w))
        g[y].append((x, w))

    def dfs(px, x, d):
        if a[x] < d:
            return 0
        ret = 1
        for y, w in g[x]:
            if y != px:
                ret += dfs(x, y, max(0, d + w))
        return ret

    print(n - dfs(0, 1, 0))


if __name__ == "__main__":
    main()
