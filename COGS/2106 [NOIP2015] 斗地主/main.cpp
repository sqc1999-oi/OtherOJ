#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <climits>
using namespace std;
const int m[] = { 13,11,12,0,1,2,3,4,5,6,7,8,9,10 };
int t[14];
map<long long, int> f;
int dfs()
{
	int sum = 0;
	for (int i = 0; i <= 13; i++) sum += t[i];
	if (sum == 0) return 0;
	long long s = 0;
	for (int i = 0; i <= 13; i++) s |= (long long)t[i] << i * 3;
	if (f[s] != 0) return f[s];
	int ret = INT_MAX;
	int p = 0;
	while (t[p] == 0) p++;
	if (p <= 13)
	{
		t[p]--;
		ret = min(ret, dfs() + 1);
		for (int i = p + 1; i <= 13; i++)
		{
			if (t[i] >= 3)
			{
				t[i] -= 3;
				ret = min(ret, dfs() + 1);
				t[i] += 3;
			}
			if (t[i] == 4)
			{
				t[i] -= 4;
				for (int j = p + 1; j <= 13; j++)
					if (i != j&&t[j] >= 1)
					{
						t[j]--;
						ret = min(ret, dfs() + 1);
						t[j]++;
					}
				t[i] += 4;
			}
		}
		t[p]++;
		for (int i = p;; i++)
			if (i <= 11 && t[i] >= 1)
			{
				t[i]--;
				if (i - p + 1 >= 5) ret = min(ret, dfs() + 1);
			}
			else
			{
				for (int j = p; j < i; j++) t[j]++;
				break;
			}
		if (t[p] >= 2)
		{
			t[p] -= 2;
			ret = min(ret, dfs() + 1);
			for (int i = p + 1; i <= 13; i++)
			{
				if (t[i] >= 3)
				{
					t[i] -= 3;
					ret = min(ret, dfs() + 1);
					t[i] += 3;
				}
				if (t[i] == 4)
				{
					t[i] -= 4;
					for (int j = p + 1; j <= 13; j++)
						if (i != j&&t[j] >= 2)
						{
							t[j] -= 2;
							ret = min(ret, dfs() + 1);
							t[j] += 2;
						}
					t[i] += 4;
				}
			}
			t[p] += 2;
			for (int i = p;; i++)
				if (i <= 11 && t[i] >= 2)
				{
					t[i] -= 2;
					if (i - p + 1 >= 3) ret = min(ret, dfs() + 1);
				}
				else
				{
					for (int j = p; j < i; j++) t[j] += 2;
					break;
				}
		}
		if (t[p] >= 3)
		{
			t[p] -= 3;
			ret = min(ret, dfs() + 1);
			for (int i = p + 1; i <= 13; i++)
			{
				if (t[i] >= 1)
				{
					t[i]--;
					ret = min(ret, dfs() + 1);
					t[i]++;
				}
				if (t[i] >= 2)
				{
					t[i] -= 2;
					ret = min(ret, dfs() + 1);
					t[i] += 2;
				}
			}
			t[p] += 3;
			for (int i = p;; i++)
				if (i <= 11 && t[i] >= 3)
				{
					t[i] -= 3;
					if (i - p + 1 >= 2) ret = min(ret, dfs() + 1);
				}
				else
				{
					for (int j = p; j < i; j++) t[j] += 3;
					break;
				}
		}
		if (t[p] == 4)
		{
			t[p] -= 4;
			ret = min(ret, dfs() + 1);
			for (int i = p + 1; i <= 13; i++)
				if (t[i] >= 1)
					for (int j = p + 1; j <= 13; j++)
						if (i != j)
						{
							if (t[j] >= 1)
							{
								t[i]--;
								t[j]--;
								ret = min(ret, dfs() + 1);
								t[i]++;
								t[j]++;
							}
							if (t[i] >= 2 && t[j] >= 2)
							{
								t[i] -= 2;
								t[j] -= 2;
								ret = min(ret, dfs() + 1);
								t[i] += 2;
								t[j] += 2;
							}
						}
			t[p] += 4;
		}
	}
	f[s] = ret;
	return ret;
}
int main()
{
	freopen("landlords.in", "r", stdin);
	freopen("landlords.out", "w", stdout);
	int T, n;
	scanf("%d%d", &T, &n);
	while (T--)
	{
		memset(t, 0x00, sizeof t);
		for (int i = 1; i <= n; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			t[m[a]]++;
		}
		printf("%d\n", dfs());
	}
}
