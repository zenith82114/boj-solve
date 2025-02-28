# Q1933 - Sweeping + priority queue
# Date: 2024.8.16

import sys
import heapq


def main() -> None:
    rd = sys.stdin.readline
    n = int(rd())
    b = [tuple(map(int, rd().split())) for _ in range(n)]
    e = []
    for j in range(n):
        l, _, r = b[j]
        e.append((l, j))
        e.append((r, -1))
    e.sort()

    pq = []
    ans = []
    h_last = 0
    i = 0
    while i < len(e):
        x = e[i][0]
        ni = i
        while ni < len(e) and e[ni][0] == x:
            j = e[ni][1]
            if j > -1:
                _, h, r = b[j]
                heapq.heappush(pq, (-h, r))
            ni += 1
        i = ni

        while pq and pq[0][1] <= x:
            heapq.heappop(pq)
        h = -pq[0][0] if pq else 0
        if h_last != h:
            ans.append(x)
            ans.append(h)
            h_last = h

    print(*ans)


if __name__ == "__main__":
    main()
