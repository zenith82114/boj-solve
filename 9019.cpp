/*
 * Q9019 - Bidirectional BFS
 * Date: 2021.7.25
 */

#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

constexpr int FROM_A = 1, FROM_B = 0, NONE = -1;
const char OP[5] = { 'D','D','S','L','R' };
char op_pred[10000], op_succ[10000], path[10000];
int pred[10000], succ[10000], neighbors[5];
int visitor[10000];

void get_neighbors(int N, int from)
{
	if (from == FROM_A) {
		neighbors[1] = (N << 1) % 10000;
		neighbors[2] = N ? N - 1 : 9999;
		neighbors[3] = (N % 1000) * 10 + N / 1000;
		neighbors[4] = (N % 10) * 1000 + N / 10;
	} else {
		neighbors[0] = N >> 1;
		neighbors[1] = neighbors[0] + 5000;
		neighbors[2] = (N + 1) % 10000;
		neighbors[3] = (N % 10) * 1000 + N / 10;
		neighbors[4] = (N % 1000) * 10 + N / 1000;
	}
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int TC;
	int A, B, n, m, nn, v;
	bool done;
	
	cin >> TC;
	while (TC--) {
		queue<int> Q;
		fill_n(visitor, 10000, NONE);
		cin >> A >> B;
		visitor[A] = FROM_A; Q.push(A);
		visitor[B] = FROM_B; Q.push(B);
		
		done = false;
		while (!done) {
			n = Q.front(); Q.pop();
			v = visitor[n];
			get_neighbors(n, v);
			for (int i = v; i < 5; ++i) {
				if (i < 2 && (n & 1) && v == FROM_B)
					continue;
				nn = neighbors[i];
				if (visitor[nn] == v)
					continue;
				if (v == FROM_A) {
					pred[nn] = n;
					op_pred[nn] = OP[i];
				} else {
					succ[nn] = n;
					op_succ[nn] = OP[i];
				}
				if (visitor[nn] == NONE) {
					visitor[nn] = v;
					Q.push(nn);
				} else {
					m = 0;
					n = nn;
					while (n != A) {
						path[m++] = op_pred[n];
						n = pred[n];
					}
					for (; m > 0; cout << path[--m]);
					n = nn;
					while (n != B) {
						cout << op_succ[n];
						n = succ[n];
					}
					cout << '\n';
					done = true;
					break;
				}
			}
		}
	}

	return 0;
}