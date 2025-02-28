# Q31642 - Dijkstra's
# Date: 2024.9.25

import sys
import heapq


def main() -> None:
    rd = sys.stdin.readline
    N, M, C, R, K = map(int, rd().split())
    g = [list() for _ in range(N + 1)]
    for _ in range(M):
        x, y, w = map(int, rd().split())
        g[x].append((y, w))
        g[y].append((x, w))

    src = [set() for _ in range(N + 1)]
    pq = [(0, x, x) for x in range(1, C + 1)]
    while pq:
        d, s, x = heapq.heappop(pq)
        if len(src[x]) == K or s in src[x]:
            continue
        src[x].add(s)
        for y, w in g[x]:
            if len(src[y]) < K and d + w <= R:
                heapq.heappush(pq, (d + w, s, y))

    ans = []
    for x in range(C + 1, N + 1):
        if len(src[x]) == K:
            ans.append(x)
    print(len(ans))
    print(*ans, sep='\n')


if __name__ == "__main__":
    main()
