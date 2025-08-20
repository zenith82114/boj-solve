"""
# Q1140 - greedy, LP
# Date: 2025.8.20
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()

    T, k1, p1, k2, p2 = map(int, rd().split())
    if p1*k2 > p2*k1:
        k1, p1, k2, p2 = k2, p2, k1, p1

    ans = 10*T
    if 10*k1 <= p1:
        pass
    elif 10*k2 <= p2:
        for x in [0, (T + k1 - 1)//k1, max(0, (T - 1)//k1)]:
            z = max(0, T - k1*x)
            ans = min(ans, p1*x + 10*z)
    elif k1*k1 <= T:
        for y in range(k1):
            t = max(0, T - k2*y)
            for x in [0, (t + k1 - 1)//k1, max(0, (t - 1)//k1)]:
                z = max(0, t - k1*x)
                ans = min(ans, p1*x + p2*y + 10*z)
    else:
        for x in range((T + k1 - 1)//k1 + 1):
            t = max(0, T - k1*x)
            for y in [0, (t + k2 - 1)//k2, max(0, (t - 1)//k2)]:
                z = max(0, t - k2*y)
                ans = min(ans, p1*x + p2*y + 10*z)
    print(ans)


if __name__ == "__main__":
    main()
