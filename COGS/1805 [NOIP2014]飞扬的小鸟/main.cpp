#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
using namespace std;
int lb[10001], ub[10001], x[10001], y[10001], f[10001][1001], cnt[10001], s[10001];
int main()
{
	ifstream cin("birda.in");
	ofstream cout("birda.out");
	ios::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i <= n; i++) lb[i] = 1, ub[i] = m;
	for (int i = 0; i < n; i++)	cin >> x[i] >> y[i];
	for (int i = 1; i <= k; i++)
	{
		int p, l, h;
		cin >> p >> l >> h;
		lb[p] = l + 1;
		ub[p] = h - 1;
		cnt[p]++;
	}
	for (int i = 1; i < n; i++) s[i] = s[i - 1] + cnt[i];
	memset(f, 0x7f, sizeof f);
	for (int i = 1; i <= m; i++) f[0][i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			int k = min(j + x[i - 1], m);
			f[i][k] = min(f[i][k], f[i][j] + 1);
			if (j >= lb[i - 1] && j <= ub[i - 1]) f[i][k] = min(f[i][k], f[i - 1][j] + 1);
		}
		for (int j = lb[i]; j <= ub[i]; j++)
			if (j + y[i - 1] >= lb[i - 1] && j + y[i - 1] <= ub[i - 1]) f[i][j] = min(f[i][j], f[i - 1][j + y[i - 1]]);
	}
	int t = *min_element(f[n] + 1, f[n] + 1 + m);
	if (t < 0x7f7f7f7f)	cout << 1 << endl << t << endl;
	else
	{
		for (int i = n - 1; i >= 0; i--)
			if (*min_element(f[i] + 1 + lb[i], f[i] + 1 + ub[i]) < 0x7f7f7f7f)
			{
				cout << 0 << endl << s[i] << endl;
				break;
			}
	}
}
