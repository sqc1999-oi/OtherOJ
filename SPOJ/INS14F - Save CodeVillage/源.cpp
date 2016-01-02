#include <iostream>
#include <algorithm>
using namespace std;
const int P = 1e9 + 7, N = 1e6;
int fact[N + 1], fact_inv[N + 1];
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
int mod_inv(int a, int p)
{
	return mod_pow(a, p - 2, p);
}
int main()
{
	fact[0] = 1;
	for (int i = 1; i <= N; i++) fact[i] = (long long)fact[i - 1] * i%P;
	fact_inv[N] = mod_inv(fact[N], P);
	for (int i = N - 1; i >= 0; i--) fact_inv[i] = (long long)fact_inv[i + 1] * (i + 1) % P;
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		if (k * 2 > n) cout << (long long)fact[n] * fact_inv[n - k] % P;
		else cout << (long long)fact[k] * fact[n - 1] % P*fact_inv[k - 1] % P*fact_inv[n - k] % P;
		cout << endl;
	}
}
