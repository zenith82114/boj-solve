"""
# Q14281 - geometry, DP
# Date: 2025.12.6
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from collections import namedtuple
    INF = 10**18

    n = int(rd())
    if n < 3:
        print(0)
        return
    a = list(map(int, rd().split()))

    Segment = namedtuple('Segment', ['cost', 'start_slope', 'end_slope'],
                         defaults=[+INF, -INF, +INF])
    seg = [[Segment()] * n for _ in range(n)]

    for i in range(n):
        for j in range(i + 1, n):
            q, r = divmod(a[j] - a[i], j - i)
            y = a[i]
            cost = 0
            for k in range(i + 1, j):
                y += q + int(k > j - r)
                if a[k] < y:
                    break
                cost += a[k] - y
            else:
                seg[i][j] = Segment(cost, q, q + int(r > 0))

    Tail = namedtuple('Tail', ['cost', 'slope'],
                      defaults=[INF, None])
    ltail = [Tail()] * n
    rtail = [Tail()] * n

    for i in range(n):
        slope = -INF
        for j in range(i):
            slope = max(slope, 1 + (a[i] - a[j] - 1) // (i - j))
        cost = 0
        for j in range(i):
            cost += a[j] - (a[i] + slope * (j - i))
        ltail[i] = Tail(cost, slope)

        slope = +INF
        for j in range(i + 1, n):
            slope = min(slope, (a[j] - a[i]) // (j - i))
        cost = 0
        for j in range(i + 1, n):
            cost += a[j] - (a[i] + slope * (j - i))
        rtail[i] = Tail(cost, slope)

    dp = [[INF] * n for _ in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            if ltail[i].slope <= seg[i][j].start_slope:
                dp[i][j] = min(dp[i][j], ltail[i].cost + seg[i][j].cost)

            for k in range(j + 1, n):
                if seg[i][j].end_slope <= seg[j][k].start_slope:
                    dp[j][k] = min(dp[j][k], dp[i][j] + seg[j][k].cost)

    ans = INF
    for i in range(n):
        if ltail[i].slope <= rtail[i].slope:
            ans = min(ans, ltail[i].cost + rtail[i].cost)
        for j in range(i + 1, n):
            if seg[i][j].end_slope <= rtail[j].slope:
                ans = min(ans, dp[i][j] + rtail[j].cost)

    print(ans)


if __name__ == "__main__":
    main()
