#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5, K = 23, P = (1 << 23) - 1;
int p[K], c[N + 1][K + 1];
int main()
{
	c[1][0] = c[1][1] = 1;
	for (int i = 2; i <= N; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j <= K&&j < i; j++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) & P;
		if (i <= K) c[i][i] = 1;
	}
	p[0] = 1;
	for (int i = 1; i < K; i++) p[i] = p[i - 1] << 1;
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		k = min(k, 23);
		int ans = 0;
		for (int i = 1; i <= k; i++)
			ans = (ans + ((long long)c[n][i] * i & P) * p[i - 1] & P) & P;
		cout << ans << endl;
	}
}
