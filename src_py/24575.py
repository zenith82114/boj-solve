# Q24575 - prefix sum, sliding window
# Date: 2025.1.2

import sys


def main() -> None:
    rd = sys.stdin.readline
    _, c = map(int, rd().split())
    a = [0] * (c + 1)
    for x in map(int, rd().split()):
        a[x] += 1
    for i in range(1, c):
        a[i] += a[i - 1]

    def psum(i, j = None):
        if j is None:
            j = i
        i, j = max(0, i), min(j, c - 1)
        return a[j] - a[i - 1] if i <= j else 0

    h = (c - 1) // 2
    h2 = c - 2 + (c & 1)
    cnt = 0
    for j in range(1, h + 1):
        cnt += psum(j) * psum(c - h, j + h)

    ans = 0
    for i in range(h + 1):
        ans += psum(i) * cnt
        cnt -= psum(i + c - h) * psum(i + c - h2, i + h)
        cnt += psum(i + h + 1) * psum(i + 1 + c - h, j + h2)

    print(ans)


if __name__ == "__main__":
    main()
