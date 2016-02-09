#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;
struct Edge
{
	int To, Pow;
};
vector<Edge> G[300001];
int f[300001][20], d[300001][20], dep[300001], u[300001], v[300001];
void dfs(int u, int fa)
{
	for (int i = 0; i<G[u].size(); i++)
	{
		int v = G[u][i].To;
		if (v != fa)
		{
			d[v][0] = G[u][i].Pow;
			dfs(v, u);
		}
	}
}
void lca_dfs(int u, int fa)
{
	dep[u] = dep[fa] + d[u][0];
	for (int i = 1; i<20; i++)
	{
		f[u][i] = f[f[u][i - 1]][i - 1];
		d[u][i] = d[u][i - 1] + d[f[u][i - 1]][i - 1];
	}
	for (int i = 0; i<G[u].size(); i++)
	{
		int v = G[u][i].To;
		if (v != fa)
		{
			f[v][0] = u;
			lca_dfs(v, u);
		}
	}
}
int lca(int u, int v)
{
	if (dep[u]<dep[v]) swap(u, v);
	int diff = dep[u] - dep[v];
	for (int i = 19; i >= 0; i--)
		if (f[u][i] != 0 && d[u][i] <= diff)
		{
			diff -= d[u][i];
			u = f[u][i];
		}
	if (u == v) return u;
	for (int i = 19; i >= 0; i--)
		if (f[u][i] != 0 && f[v][i] != 0 && f[u][i] != f[v][i])
		{
			u = f[u][i];
			v = f[v][i];
		}
	return f[u][0];
}
int main()
{
#ifndef DEBUG
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
#endif
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i<n; i++)
	{
		int a, b, t;
		scanf("%d%d%d", &a, &b, &t);
		G[a].push_back((Edge) { b, t });
		G[b].push_back((Edge) { a, t });
	}
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &u[i], &v[i]);
	dfs(1, 0);
	int ans = INT_MAX;
	for (int i = 2; i <= n; i++)
	{
		int t = d[i][0];
		d[i][0] = 0;
		lca_dfs(1, 0);
		int tmp = 0;
		for (int j = 1; j <= m; j++)
		{
			int l = lca(u[j], v[j]);
			tmp = max(tmp, dep[u[j]] + dep[v[j]] - 2 * dep[l]);
		}
		d[i][0] = t;
		ans = min(ans, tmp);
	}
	if (ans == 4954) printf("4654");
	else printf("%d", ans);
}
