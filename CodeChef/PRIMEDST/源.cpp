#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <complex>
#include <cmath>
#include <iomanip>
using namespace std;
typedef complex<double> cmplx;
const int N = 50000;
const double PI = acos(-1.0);
vector<int> g[N];
bool flag[N], not_prime[300000];
int sz[N], dep[N];
cmplx a[300000];
void get_nodes(int u, int fa, vector<int> &vi)
{
	vi.push_back(u);
	for (int v : g[u])
		if (v != fa && !flag[v])
			get_nodes(v, u, vi);
}
void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (int v : g[u])
		if (v != fa && !flag[v])
		{
			calc_size(v, u);
			sz[u] += sz[v];
		}
}
void calc_dep(int u, int fa)
{
	for (int v : g[u])
		if (v != fa && !flag[v])
		{
			dep[v] = dep[u] + 1;
			calc_dep(v, u);
		}
}
void get_focus(int u, int fa, int n, int &ans, int &min)
{
	int max = n - sz[u];
	for (int v : g[u])
		if (v != fa && !flag[v])
		{
			max = ::max(max, sz[v]);
			get_focus(v, u, n, ans, min);
		}
	if (max < min)
	{
		min = max;
		ans = u;
	}
}
int rev(int x, int n)
{
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		res <<= 1;
		res |= x & 1;
		x >>= 1;
	}
	return res;
}
void dft(cmplx *a, int n, int flag)
{
	static cmplx tmp[300000];
	int lg = round(log2(n));
	for (int i = 0; i < n; i++)
		tmp[rev(i, lg)] = a[i];
	for (int i = 0, j = 2; i < lg; i++, j <<= 1)
	{
		cmplx wm(cos(flag * 2 * PI / j), sin(flag * 2 * PI / j));
		for (int k = 0; k < n; k += j)
		{
			cmplx w = 1;
			for (int l = 0; l < j / 2; l++)
			{
				cmplx u = w*tmp[k + l + j / 2], t = tmp[k + l];
				tmp[k + l] = t + u;
				tmp[k + l + j / 2] = t - u;
				w *= wm;
			}
		}
	}
	if (flag == -1) for (int i = 0; i < n; i++) tmp[i] /= n;
	for (int i = 0; i < n; i++) a[i] = tmp[i];
}
long long calc_ans(int u)
{
	vector<int> v;
	get_nodes(u, -1, v);
	int max = 0;
	for (int x : v) max = ::max(max, dep[x]);
	(++max) <<= 1;
	int n = 1;
	while (n < max) n <<= 1;
	for (int i = 0; i < n; i++) a[i] = 0;
	for (int x : v) a[dep[x]] += 1;
	dft(a, n, 1);
	for (int i = 0; i < n; i++) a[i] *= a[i];
	dft(a, n, -1);
	long long ans = 0;
	for (int i = 0; i < n; i++)
		if (!not_prime[i])
			ans += round(a[i].real());
	return ans;
}
inline long long solve(int u)
{
	calc_size(u, -1);
	int x = INT_MAX;
	get_focus(u, -1, sz[u], u, x);
	flag[u] = true;
	dep[u] = 0;
	calc_dep(u, -1);
	long long ans = calc_ans(u);
	for (int v : g[u]) if (!flag[v]) ans -= calc_ans(v);
	for (int v : g[u]) if (!flag[v]) ans += solve(v);
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	not_prime[0] = not_prime[1] = true;
	int m = sqrt(300000);
	for (int i = 2; i <= m; i++)
		if (!not_prime[i])
			for (int j = i*i; j <= 300000; j += i)
				not_prime[j] = true;
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
		g[b - 1].push_back(a - 1);
	}
	cout << fixed << setprecision(10) << solve(0) / ((double)n*(n - 1));
}
