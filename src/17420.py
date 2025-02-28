# Q17420 - greedy, sweeping
# Date: 2025.1.12

import sys


def main() -> None:
    rd = sys.stdin.readline
    d = 30
    n = int(rd())
    A = list(map(int, rd().split()))
    B = list(map(int, rd().split()))
    ans = 0
    for i in range(n):
        q = (max(0, B[i] - A[i]) + d - 1) // d
        ans += q
        A[i] += q * d
    B, A = map(list, zip(*sorted(zip(B, A))))
    i, j = 0, 0
    a_pre = 0
    while i < n:
        while j < n and B[i] == B[j]:
            j += 1
        a = 0
        for k in range(i, j):
            q = (max(0, a_pre - A[k]) + d - 1) // d
            ans += q
            a = max(a, A[k] + (q * d))
        i = j
        a_pre = a
    print(ans)


if __name__ == "__main__":
    main()
