#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 3e4;
int a[N], b[N], t[N], F[N + 1], G[N + 1], f[N + 1];

void dp(int d, int c)
{
	if (f[d] != -1) return;
	f[d] = F[d];
	for (int i = 2; i * d <= c; i++)
		if (c % (i * d) == 0)
		{
			dp(i * d, c);
			f[d] -= f[i * d];
		}
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		int n, m, c;
		cin >> n >> m >> c;
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < m; i++) cin >> b[i];
		for (int i = 1; i < n; i++)  a[i] += a[i - 1];
		for (int i = 1; i < m; i++) b[i] += b[i - 1];
		memset(F, 0x00, sizeof F);
		memset(G, 0x00, sizeof G);
		for (int d = 1; d <= c; d++)
			if (c % d == 0)
			{
				memset(t, 0x00, sizeof t);
				t[0] = 1;
				for (int i = 0; i < n; i++)
				{
					F[d] += t[a[i] % d];
					t[a[i] % d]++;
				}
				memset(t, 0x00, sizeof t);
				t[0] = 1;
				for (int i = 0; i < m; i++)
				{
					G[d] += t[b[i] % d];
					t[b[i] % d]++;
				}
			}
		memset(f, 0xff, sizeof f);
		for (int d = 1; d <= c; d++)
			if (n % d == 0) dp(d, c);
		long long ans = 0;
		for (int d = 1; d <= c; d++)
			if (c % d == 0) ans += (long long)f[d] * G[c / d];
		cout << ans << endl;
	}
}
