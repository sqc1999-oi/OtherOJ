#include <cstdio>
#include <algorithm>
using namespace std;
int a[50002];
int main()
{
#ifndef DEBUG
	freopen("2015stone.in", "r", stdin);
	freopen("2015stone.out", "w", stdout);
#endif
	int L, n, m;
	scanf("%d%d%d", &L, &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	a[n + 1] = L;
	int l = 0, r = L, ans;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		int cnt = 0, la = 0;
		for (int i = 1; i <= n; i++)
			if (a[i] - la < mid) cnt++;
			else la = a[i];
			if (a[n + 1] - la < mid) cnt++;
			if (cnt <= m)
			{
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
	}
	printf("%d", ans);
}
