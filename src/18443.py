"""
# Q18443 - dp, prefix sum
# Date: 2025.7.28
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    n, m, L = map(int, rd().split())
    s = [0]
    s.extend(map(int, rd().split()))
    s.extend(x + L for x in s[1:])
    for i in range(1, len(s)):
        s[i] += s[i - 1]

    def cost(i, j):
        mid = (i + j) // 2
        return s[j] - s[mid - 1] - s[mid] + s[i - 1] + (2*mid - i - j)*(s[mid] - s[mid - 1])

    ans, sol = 10**20, []

    for base in range(1, n + 1):
        dp = [[10**20] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = 0
        opt = [[-1] * (n + 1) for _ in range(m + 1)]

        for i in range(1, m + 1):
            for j in range(i, n + 1):
                for k in range(i - 1, j):
                    temp = dp[i - 1][k] + cost(base + k + 1, base + j)
                    if dp[i][j] > temp:
                        dp[i][j], opt[i][j] = temp, k

        if ans > dp[m][n]:
            ans, sol = dp[m][n], []
            i, j = m, n
            while i:
                k = opt[i][j]
                mid = base + ((k + 1 + j) // 2)
                sol.append(s[mid] - s[mid - 1])
                i, j = i - 1, k

    sol = sorted(x % L for x in sol)
    print(ans)
    print(*sol)


if __name__ == "__main__":
    main()
