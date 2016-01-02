#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 10, P = 2004;
int m[N];
void calc_choose(int n, int k, int p, int *f)
{
	if (n == 1) return;
	if (n & 1)
	{
		calc_choose(n - 1, k, p, f);
		for (int i = k; i > 0; i--)
			f[i] = (f[i] + f[i - 1]) % p;
	}
	else
	{
		calc_choose(n >> 1, k, p, f);
		for (int i = k; i > 0; i--)
		{
			int t = 0;
			for (int j = 0; j <= i; j++)
				t += f[j] * f[i - j];
			f[i] = t%p;
		}
	}
};
int mod_choose(int n, int k, int p)
{
	static int f[N + 1];
	memset(f, 0x00, sizeof f);
	f[0] = f[1] = 1;
	calc_choose(n, k, p, f);
	return f[k];
}
int calc(int n, int *m, int x, int p)
{
	if (x < 0) return 0;
	int ret = 0;
	for (int i = 0; i < 1 << n; i++)
	{
		int t = x, cnt = 0;
		for (int j = 0; j < n; j++) if (i & 1 << j)
		{
			cnt++;
			t -= m[j] + 1;
		}
		if (t < 0) continue;
		t += n;
		if (cnt & 1) ret -= mod_choose(t, n, p);
		else ret += mod_choose(t, n, p);
	}
	return (ret%p + p) % p;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, a, b;
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++) cin >> m[i];
	cout << (calc(n, m, b, P) - calc(n, m, a - 1, P) + P) % P;
}
