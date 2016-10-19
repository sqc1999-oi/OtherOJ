#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int P = 1e9 + 7;
char a[1002], b[202];
int f[2][201][201][2];
int main()
{
	freopen("2015substring.in", "r", stdin);
	freopen("2015substring.out", "w", stdout);
	int n, m, K;
	scanf("%d%d%d%s%s", &n, &m, &K, a + 1, b + 1);
	f[0][0][0][0] = 1;
	for (int i = 0; i < n; i++)
	{
		memset(f[(i + 1) & 1], 0x00, sizeof f[(i + 1) & 1]);
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= K; k++)
				if (i < n)
				{
					(f[(i + 1) & 1][j][k][0] += f[i & 1][j][k][0]) %= P;
					(f[(i + 1) & 1][j][k][0] += f[i & 1][j][k][1]) %= P;
					if (j < m&&a[i + 1] == b[j + 1])
					{
						(f[(i + 1) & 1][j + 1][k][1] += f[i & 1][j][k][1]) %= P;
						if (k < K)
						{
							(f[(i + 1) & 1][j + 1][k + 1][1] += f[i & 1][j][k][0]) %= P;
							(f[(i + 1) & 1][j + 1][k + 1][1] += f[i & 1][j][k][1]) %= P;
						}
					}
				}
	}
	printf("%d", (f[n & 1][m][K][0] + f[n & 1][m][K][1]) % P);
}
