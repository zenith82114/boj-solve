# Q25582 - Manacher's
# Date: 2024.8.31

import sys
from string import ascii_lowercase


def main() -> None:
    S = f"*{'*'.join(input())}*"

    def manacher(S, f):
        N = len(S)
        r, p = 0, 0
        A = [0] * N
        for i in range(N):
            if S[i] != f[S[i]]:
                A[i] = 0
            else:
                A[i] = min(A[2 * p - i], r - i) if i <= r else 0
                while (
                    i - A[i] - 1 >= 0 and
                    i + A[i] + 1 < N and
                    S[i - A[i] - 1] == f[S[i + A[i] + 1]]
                ):
                    A[i] += 1
            if r < i + A[i]:
                r, p = i + A[i], i
        return max(A)

    f = {i: 'X' for i in ascii_lowercase}
    for a, b in [
        ('b','d'),('p','q'),
        ('i','i'),('m','m'),('v','v'),('w','w'),
        ('l','l'),('o','o'),('x','x'),
        ('*','*')
    ]:
        f[a] = b
        f[b] = a
    ans = manacher(S, f)
    f = {i: 'X' for i in ascii_lowercase}
    for a, b in [
        ('b','q'),('p','d'),
        ('u','n'),
        ('s','s'),('z','z'),
        ('l','l'),('o','o'),('x','x'),
        ('*','*')
    ]:
        f[a] = b
        f[b] = a
    ans = max(ans, manacher(S, f))
    if ans == 0:
        print("NOANSWER")
    else:
        print(ans)


if __name__ == "__main__":
    main()
