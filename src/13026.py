"""
# Q13026 - maximum flow
# Date: 2025.9.21
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from collections import deque

    sieve = [1] * 20001
    for x in range(2, 20001):
        if sieve[x]:
            for y in range(x*x, 20001, x):
                sieve[y] = 0

    n = int(rd())
    a = list(map(int, rd().split()))

    g = [[] for _ in range(n + 2)]
    cap = []

    def add_edge(i, j, c):
        g[i].append((j, len(cap)))
        cap.append(c)
        g[j].append((i, len(cap)))
        cap.append(0)

    for i in range(n):
        if a[i] & 1:
            add_edge(n, i, 2)
            for j in range(n):
                if sieve[a[i] + a[j]]:
                    add_edge(i, j, 1)
        else:
            add_edge(i, n + 1, 2)

    pred = []

    def bfs():
        pred[:] = [None] * (n + 2)
        q = deque([n])
        while q:
            i = q.popleft()
            for j, e in g[i]:
                if pred[j] is None and cap[e] > 0:
                    pred[j] = (i, e)
                    if j == n + 1:
                        return True
                    q.append(j)
        return False

    f = 0
    while bfs():
        f += 1
        i = n + 1
        while i != n:
            j, e = pred[i]
            cap[e] -= 1
            cap[e^1] += 1
            i = j

    print("Possible" if f == n else "Impossible")


if __name__ == "__main__":
    main()
