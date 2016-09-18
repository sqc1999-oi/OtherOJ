#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
int a[129][129];
int main()
{
	ifstream cin("wireless.in");
	ofstream cout("wireless.out");
	ios::sync_with_stdio(false);
	int d, n;
	cin >> d >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		cin >> a[x][y];
	}
	int ans = 0, cnt = 0;
	for (int i = 0; i <= 128; i++)
	{
		for (int j = 0; j <= 128; j++)
		{
			int sum = 0;
			for (int k = max(0, i - d); k <= min(128, i + d); k++)
			{
				for (int l = max(0, j - d); l <= min(128, j + d); l++)
				{
					sum += a[k][l];
				}
			}
			if (sum > ans) ans = sum, cnt = 1;
			else if (sum == ans) cnt++;
		}
	}
	cout << cnt << ' ' << ans << endl;
}
