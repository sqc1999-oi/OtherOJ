#include <cstdio>
#include <algorithm>
using namespace std;
int a[40][40];
int main()
{
#ifndef DEBUG
	freopen("2015magic.in", "r", stdin);
	freopen("2015magic.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	int x = 1, y = n / 2 + 1;
	a[x][y] = 1;
	for (int i = 2; i <= n*n; i++)
	{
		if (x == 1 && y == n) x++;
		else if (x == 1) x = n, y++;
		else if (y == n) x--, y = 1;
		else if (a[x - 1][y + 1] == 0) x--, y++;
		else x++;
		a[x][y] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}
