# Q13186 - Burnside's lemma, Euler phi function, prefix sum
# Date: 2024.7.7
#
# Note: PyPy3 AC, Python 3 TLE

def div(a, b, p):
    return a * pow(b, p-2, p) % p


def main() -> None:
    p = 10**9 + 7
    n, k = map(int, input().split())

    f = list(range(n+1))
    for i in range(2, n+1):
        if f[i] == i:
            for j in range(i, n+1, i):
                f[j] -= f[j] // i

    for i in range(1, n+1):
        f[i] = (div(f[i], i, p) + f[i-1]) % p

    ans = 0
    for m in range(1, n+1):
        ans = (ans + div(pow(k, m, p), m, p) * f[n//m]) % p

        if m % 2 == 0:
            ans = (ans + div((k+1) * pow(k, m//2, p), 2, p)) % p
        else:
            ans = (ans + pow(k, m//2 + 1, p)) % p

    print((div(ans, 2, p) + 1) % p)


if __name__ == "__main__":
    main()
