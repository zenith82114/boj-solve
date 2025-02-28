# Q28574 - greedy, binary search
# Date: 2024.10.1

import sys
import bisect


def main() -> None:
    rd = sys.stdin.readline
    n, _ = map(int, rd().split())
    a = [(0, 0)]
    a.extend(tuple(map(int, rd().split())) for _ in range(n))
    a.sort()
    psum = [1]
    for i in range(1, n + 1):
        psum.append(psum[-1] + a[i][0])
    smin = [a[-1][1]] * (n + 1)
    for i in reversed(range(n)):
        smin[i] = min(a[i][1], smin[i + 1])
    jumps = [0]
    jumps.extend(i for i in range(1, n + 1) if psum[i - 1] < a[i][0])

    for x in map(int, rd().split()):
        i = bisect.bisect_left(psum, x)
        if i > n:
            print(-1, end=' ')
        else:
            last_jump = jumps[bisect.bisect_right(jumps, i) - 1]
            print(smin[last_jump], end=' ')


if __name__ == "__main__":
    main()
