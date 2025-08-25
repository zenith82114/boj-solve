"""
# Q22900 - DP
# Date: 2025.8.25
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    sys.setrecursionlimit(303030)

    n = int(rd())
    adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        x, y, w = map(int, rd().split())
        adj[x].append(y)
        adj[y].append(x)

    par = [0] * (n + 1)
    f = [0] * (n + 1)

    def dfs(px, x):
        par[x] = px
        f[x] = 0
        for y in adj[x]:
            if y != px:
                dfs(x, y)
                f[x] += (f[y] == 0)
    dfs(0, 1)

    g = [-1] * (n + 1)
    g[1] = 0

    def get_g(x):
        if g[x] == -1:
            g[x] = int(f[par[x]] == int(f[x] == 0) and not get_g(par[x]))
        return g[x]

    for x in range(1, n + 1):
        print(['Portuga', 'Zeze'][f[x] > 0 or get_g(x)])


if __name__ == "__main__":
    main()
