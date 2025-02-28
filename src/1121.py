# Q1121 - geometry, DP
# Date: 2025.2.25

def main() -> None:
    import sys
    rd = sys.stdin.readline

    rd()
    a = sorted(map(int, rd().split()))
    k = int(rd())

    L = 50001
    dp = [[0] * (L + 1) for _ in range(k)]
    dp[0][0] = 1
    ans = 0

    for x in a:
        for d in range(x + 1, L + 1):
            ans += dp[k - 1][d]
        for j in reversed(range(1, k)):
            for d in range(L + 1):
                dp[j][min(d + x, L)] += dp[j - 1][d]

    print(ans)


if __name__ == "__main__":
    main()
