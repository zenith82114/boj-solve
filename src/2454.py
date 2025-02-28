# Q2454 - Greedy
# Date: 2024.8.3

import sys


def main() -> None:
    rd = sys.stdin.readline
    inf = int(1e9)
    n, k = map(int, rd().split())
    tree = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        x, y = map(int, rd().split())
        tree[x].append(y)
        tree[y].append(x)

    def dfs(px, x) -> tuple:
        sum_a = 0
        min1_b, min2_b = inf, inf
        for y in tree[x]:
            if y == px:
                continue
            a, b = dfs(x, y)
            sum_a += a
            if min1_b > b:
                min1_b, min2_b = b, min1_b
            elif min2_b > b:
                min2_b = b
        if min1_b + min2_b <= k:
            return (sum_a - 1, inf)
        if min1_b <= k:
            return (sum_a, min1_b + 1)
        return (sum_a + 1, 1)

    print(dfs(0, 1)[0])


if __name__ == "__main__":
    sys.setrecursionlimit(300005)
    main()
