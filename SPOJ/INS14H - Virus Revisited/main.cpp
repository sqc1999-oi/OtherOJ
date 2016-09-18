#include <iostream>
#include <algorithm>
using namespace std;
const int P = 1e9 + 7, N = 100;
int fact[N * 2 + 1], fact_inv[N * 2 + 1], f[N + 1][N + 1];
int mod_pow(int a, int b, int p)
{
	long long ret = 1, t = a;
	while (b > 0)
	{
		if (b & 1) ret = ret*t % p;
		t = t*t%p;
		b >>= 1;
	}
	return ret;
}
int mod_inv(int a, int p) { return mod_pow(a, p - 2, p); }
int mod_choose(int n, int k, int p) { return (long long)fact[n] * fact_inv[k] % p*fact_inv[n - k] % p; }
int main()
{
	fact[0] = 1;
	for (int i = 1; i <= N * 2; i++) fact[i] = (long long)fact[i - 1] * i%P;
	fact_inv[N * 2] = mod_inv(fact[N * 2], P);
	for (int i = N * 2 - 1; i >= 0; i--) fact_inv[i] = (long long)fact_inv[i + 1] * (i + 1) % P;
	for (int i = 0; i <= N; i++) f[1][i] = mod_choose(2 * i, i, P);
	for (int i = 2; i <= N; i++)
		for (int j = 0; j <= N; j++)
			for (int k = 0; k <= j; k++)
				f[i][j] = (f[i][j] + (long long)f[i - 1][j - k] * mod_choose(2 * j, 2 * k, P) % P*mod_choose(2 * k, k, P) % P) % P;
	ios::sync_with_stdio(false);
	int Q;
	cin >> Q;
	while (Q--)
	{
		int n, T;
		cin >> n >> T;
		cout << (T % 2 == 0 ? f[n][T / 2] : 0) << endl;
	}
}
