"""
# Q25490 - DnC, two pointers, prefix sum
# Date: 2026.3.16
"""

def dnc(l, r) -> int:
    if l == r:
        return (a[l]**2) % MOD
    m = (l + r) // 2
    ans = dnc(l, m) + dnc(m + 1, r)

    rmin[m], rmax[m] = 10**9, 0
    smin[m], smax[m], sminmax[m] = 0, 0, 0

    for j in range(m + 1, r + 1):
        rmin[j] = min(rmin[j - 1], a[j])
        rmax[j] = max(rmax[j - 1], a[j])
        smin[j] = smin[j - 1] + rmin[j]
        smax[j] = smax[j - 1] + rmax[j]
        sminmax[j] = sminmax[j - 1] + rmin[j]*rmax[j]

    lmin, lmax = 10**9, 0
    p, q = m + 1, m + 1

    for i in reversed(range(l, m + 1)):
        lmin = min(lmin, a[i])
        lmax = max(lmax, a[i])
        while p <= r and rmin[p] >= lmin: p += 1
        while q <= r and rmax[q] <= lmax: q += 1
        if p <= q:
            ans += (p - m - 1)*lmin*lmax
            ans += (smin[q - 1] - smin[p - 1])*lmax
            ans += (sminmax[r] - sminmax[q - 1])
        else:
            ans += (q - m - 1)*lmin*lmax
            ans += lmin*(smax[p - 1] - smax[q - 1])
            ans += (sminmax[r] - sminmax[p - 1])

    return ans % MOD


if __name__ == "__main__":
    MOD = 10**9 + 7
    n = int(input())
    a = list(map(int, input().split()))
    rmin = [0] * n
    rmax = [0] * n
    smin = [0] * n
    smax = [0] * n
    sminmax = [0] * n
    print(dnc(0, n - 1))
