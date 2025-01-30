# Q24457 - greedy, DP
# Date: 2025.1.30

def main() -> None:
    import sys
    rd = sys.stdin.readline
    n = int(rd())
    E = list(map(int, rd().split()))
    C = list(map(int, rd().split()))
    C, E = map(list, zip(*sorted(zip(C, E))))
    dp = [[0] * (n + 1 - i) for i in range(n)]

    dp[-1][1] = E[-1]
    for i in reversed(range(n - 1)):
        for j in range(1, len(dp[i])):
            dp[i][j] = max(0, dp[i + 1][j - 1] + E[i] - (j - 1) * C[i])
            if j < len(dp[i + 1]):
                dp[i][j] = max(dp[i][j], dp[i + 1][j])
    print(max(dp[0]))


if __name__ == "__main__":
    main()
