"""
# Q20135 - circulation
# Date: 2025.11.16
"""

def main() -> None:
    import sys
    rd = lambda: sys.stdin.readline().rstrip()
    from collections import deque

    n, m = map(int, rd().split())
    demand = [0] + list(map(int, rd().split()))
    if sum(demand) != 0:
        print(-1)
        return

    g = [[] for _ in range(n + 2)]
    cap = []
    lb = []

    def add_edge(x, y, c):
        g[x].append((y, len(cap)))
        cap.append(c)
        g[y].append((x, len(cap)))
        cap.append(0)

    for _ in range(m):
        x, y, l, u = map(int, rd().split())
        demand[x] -= l
        demand[y] += l
        add_edge(x, y, u - l)
        lb.append(l)
    for x in range(1, n + 1):
        if demand[x] > 0:
            add_edge(0, x, demand[x])
        if demand[x] < 0:
            add_edge(x, n + 1, -demand[x])

    pred = []

    def bfs():
        pred[:] = [None] * (n + 2)
        pred[0] = (-1, -1)
        q = deque([0])
        while q:
            x = q.popleft()
            for y, e in g[x]:
                if pred[y] is None and cap[e] > 0:
                    pred[y] = (x, e)
                    if y == n + 1:
                        return True
                    q.append(y)
        return False

    flow = 0
    while bfs():
        df = 10**9
        y = n + 1
        while y > 0:
            x, e = pred[y]
            df = min(df, cap[e])
            y = x

        flow += df
        y = n + 1
        while y > 0:
            x, e = pred[y]
            cap[e] -= df
            cap[e^1] += df
            y = x

    if flow != sum(max(0, _) for _ in demand):
        print(-1)
    else:
        print(1)
        for i in range(m):
            print(lb[i] + cap[2*i + 1])


if __name__ == "__main__":
    main()
