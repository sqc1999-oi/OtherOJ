#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 10, P = 2004, M = 4;
const int A[] = { 2,3,5,7 };
int m[N];
int mod_choose(int n, int k, int p)
{
	static int a[M];
	memset(a, 0x00, sizeof a);
	for (int i = 2; i <= k; i++)
	{
		int t = i;
		for (int j = 0; j < M; j++)
			while (t%A[j] == 0)
			{
				t /= A[j];
				a[j]++;
			}
	}
	int ret = 1;
	for (int i = n - k + 1; i <= n; i++)
	{
		int t = i;
		for (int j = 0; j < M; j++)
			while (a[j]>0 && t%A[j] == 0)
			{
				t /= A[j];
				a[j]--;
			}
		ret = (long long)ret*t%p;
	}
	return ret;
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
