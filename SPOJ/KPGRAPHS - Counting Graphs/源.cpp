#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000, P = 1e9 + 7, INV_2 = 500000004;
int con[N + 1], euler[N + 1], bipart[N + 1], binom[N + 1][N + 1], tmp[N + 1], tmp2[N + 1];
int pow(int a, int b, int p)
{
	long long ret = 1, t = a;
	while (b > 0)
	{
		if (b & 1) (ret *= t) %= p;
		(t *= t) %= p;
		b >>= 1;
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	for (int i = 0; i <= N; i++)
	{
		binom[i][0] = 1;
		for (int j = 1; j <= i; j++)
			binom[i][j] = (binom[i-1][j] + binom[i-1][j-1]) % P;
	}
	for (int i = 0; i <= N; i++)
		tmp[i] = pow(2, binom[i][2], P);
	for (int i = 1; i <= N; i++)
	{
		con[i] = tmp[i];
		for (int j = 1; j < i; j++)
			con[i] = (con[i] - (long long)binom[i - 1][j - 1] * con[j] % P * tmp[i - j] % P + P) % P;
	}
	for (int i=1; i <= N; i++)
	{
		euler[i] = tmp[i - 1];
		for (int j = 1; j < i; j++)
			euler[i] = (euler[i] - (long long)binom[i - 1][j - 1] * euler[j] % P * tmp[i-j-1] % P + P) % P;
	}
	tmp[0] = 1;
	for (int i = 1; i <= N; i++)
	{
		tmp[i] = 0;
		for (int j = 0; j <= i; j++)
			tmp[i] = (tmp[i] + (long long)binom[i][j] * pow(2, j * (i - j), P) % P) % P;
	}
	for (int i = 1; i <= N; i++)
	{
		tmp2[i] = (long long)tmp[i] * INV_2 % P;
		for (int j = 1; j < i; j++)
			tmp2[i] = (tmp2[i] - (long long)binom[i - 1][j - 1] * tmp2[j] % P * tmp[i - j] % P + P) % P;
	}
	for (int i = 1; i <= N; i++)
	{
		bipart[i] = tmp2[i];
		for (int j = 1; j < i; j++)
			bipart[i] = (bipart[i] + (long long)binom[i - 1][j - 1] * tmp2[j] % P * bipart[i - j] % P) % P;
	}
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		cout << "Connected: " << con[n] << endl
			 << "Eulerian: " << euler[n] << endl
			 << "Bipartite: " << bipart[n] << endl
			 << endl;
	}
}
