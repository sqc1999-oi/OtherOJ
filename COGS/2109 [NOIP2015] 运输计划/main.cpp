#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <cstdarg>
using namespace std;
const int N = 3e5;
struct edge
{
	int to, pow, next;
	edge(int to, int pow, int next) :to(to), pow(pow), next(next) {}
	edge() = default;
} e[(N - 1) * 2];
int g[N];
struct { int fa, pow, dis, dep; } p[N];
struct { int u, v, lca, dis; } d[N];
void add_edge(int from, int to, int pow)
{
	static int cnt = 0;
	e[cnt] = edge(to, pow, g[from]);
	g[from] = cnt++;
}
void dfs(int u, int fa)
{
	for (int i = g[u]; i != -1; i = e[i].next)
	{
		edge &v = e[i];
		if (v.to != fa)
		{
			p[v.to].fa = u;
			p[v.to].pow = v.pow;
			p[v.to].dis = p[u].dis + v.pow;
			p[v.to].dep = p[u].dep + 1;
			dfs(v.to, u);
		}
	}
}
namespace lca
{
	const int K = 20;
	int f[N][K];
	void dfs(int u)
	{
		f[u][0] = p[u].fa;
		for (int i = 1; i < K; i++) f[u][i] = f[f[u][i - 1]][i - 1];
		for (int i = g[u]; i != -1; i = e[i].next)
		{
			edge &v = e[i];
			if (v.to != p[u].fa) dfs(v.to);
		}
	}
	int get_lca(int u, int v)
	{
		if (p[u].dep < p[v].dep) swap(u, v);
		for (int i = K - 1; i >= 0; i--)
			if (p[f[u][i]].dep >= p[v].dep)
				u = f[u][i];
		if (u == v) return u;
		for (int i = K - 1; i >= 0;i--)
			if (f[u][i] != f[v][i])
			{
				u = f[u][i];
				v = f[v][i];
			}
		return p[u].fa;
	}
}
namespace bin
{
	int flag[N], max, cnt, dcnt;
	void dfs(int u)
	{
		for (int i = g[u]; i != -1; i = e[i].next)
		{
			edge &v = e[i];
			if (v.to != p[u].fa)
			{
				int tmp = cnt;
				cnt = 0;
				dfs(v.to);
				cnt += tmp;
			}
		}
		cnt += flag[u];
		if (cnt == dcnt) max = std::max(max, p[u].pow);
	}
}
char get_ch(FILE *in)
{
	const int S = 10000000;
	static char buf[S];
	static int pos = S;
	if (pos == S)
	{
		fread(buf, 1, S, in);
		pos = 0;
	}
	return buf[pos++];
}
void read(FILE *in, int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--)
	{
		int &x = *va_arg(li, int *);
		x = 0;
		char ch;
		do ch = get_ch(in);
		while (!isdigit(ch));
		do
		{
			(x *= 10) += ch - '0';
			ch = get_ch(in);
		} while (isdigit(ch));
	}
	va_end(li);
}
int main()
{
	FILE *in = fopen("transport.in", "r"), *out = fopen("transport.out", "w");
	int n, m;
	read(in, 2, &n, &m);
	memset(g, 0xff, sizeof g);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, t;
		read(in, 3, &a, &b, &t);
		a--, b--;
		add_edge(a, b, t);
		add_edge(b, a, t);
	}
	dfs(0, 0);
	lca::dfs(0);
	for (int i = 0; i < m; i++)
	{
		read(in, 2, &d[i].u, &d[i].v);
		d[i].u--, d[i].v--;
		d[i].lca = lca::get_lca(d[i].u, d[i].v);
		d[i].dis = p[d[i].u].dis + p[d[i].v].dis - p[d[i].lca].dis * 2;
	}
	int l = 0, r = N * 1000, ans;
	using namespace bin;
	while (l <= r)
	{
		int mid = (l + r) / 2, max = 0, cnt = 0;
		memset(flag, 0x00, sizeof flag);
		for (int i = 0; i < m; i++)
			if (d[i].dis > mid)
			{
				flag[d[i].u]++;
				flag[d[i].v]++;
				flag[d[i].lca] -= 2;
				max = std::max(max, d[i].dis);
				cnt++;
			}
		if (cnt > 0)
		{
			bin::max = 0;
			bin::dcnt = cnt;
			bin::dfs(0);
		}
		if (cnt == 0 || max - bin::max <= mid)
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	fprintf(out, "%d\n", ans);
}
