/*
 * Q11401 - Binomial coefficients using mult. inverse
 * Date: 2021.7.10
 */

#include <iostream>
using namespace std;

#define M 1000000007
uint64_t powmod(uint32_t A, uint32_t B, uint32_t C)
{
	uint64_t a = A % C;
	uint32_t b = B;
	uint64_t R = b & 1 ? a : 1;
	while (b >>= 1) {
		a = (a * a) % C;
		if (b & 1)
			R = (R * a) % C;
	}
	return R;
}
int main()
{
	cin.tie(0); ios::sync_with_stdio(0);
	uint32_t N, K;
    uint64_t R = 1;
    
    cin >> N >> K;
	if (2 * K > N) K = N - K;
	for (uint32_t n = N - K + 1; n <= N; ++n)
		R = (R * n) % M;
	for (uint32_t k = 2; k <= K; ++k) {
		R = (R * powmod(k, M - 2, M)) % M;
	}
	cout << R << '\n';
}