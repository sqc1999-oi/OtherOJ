#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4018)
#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
struct edge
{
	int to, w;
};
const int N = 100000, M = 17;
vector<int> e, g[N], sum[N], sumc[N * 2];
vector<edge> vg[N];
vector<pii> p[N];
int sz[N], dep[N], f[N][M], id[N], cnt, ch[N], a[N], r[N];
bool flag[N], inq[N];
bool check(int u, int v) { return u != v&&!flag[u]; }
void dfs(int u, int fa)
{
	id[u] = cnt++;
	f[u][0] = fa;
	for (int i = 1; i < M; i++) f[u][i] = f[f[u][i - 1]][i - 1];
	for (int x : g[u])
	{
		int v = e[x];
		if (check(v, fa))
		{
			dep[v] = dep[u] + 1;
			dfs(v, u);
		}
	}
}
void calc_size(int u, int fa)
{
	sz[u] = 1;
	for (int x : g[u])
	{
		int v = e[x];
		if (check(v, fa))
		{
			calc_size(v, u);
			sz[u] += sz[v];
		}
	}
}
void get_nodes(int u, int fa, int d, int focus, int fe)
{
	sum[focus][d]++;
	sumc[fe][d]++;
	p[u].push_back(pii(focus, d));
	for (int x : g[u])
	{
		int v = e[x];
		if (check(v, fa)) get_nodes(v, u, d + 1, focus, fe);
	}
}
void calc_focus(int u, int fa, int n, int &focus, int &min)
{
	int max = n - sz[u];
	for (int x : g[u])
	{
		int v = e[x];
		if (check(v, fa))
		{
			max = ::max(max, sz[v]);
			calc_focus(v, u, n, focus, min);
		}
	}
	if (max < min)
	{
		min = max;
		focus = u;
	}
}
void calc_sum(vector<int> &v)
{
	for (int i = 1; i < v.size(); i++) v[i] += v[i - 1];
}
int query(int u, int d)
{
	static auto get = [](vector<int> &v, int x) { return v[min(x, (int)v.size() - 1)]; };
	int ret = 0;
	for (int i = p[u].size() - 1; i >= 0; i--)
	{
		int dis = d - p[u][i].second;
		if (dis < 0) continue;
		ret += get(sum[p[u][i].first], dis);
		if (i < p[u].size() - 1) ret -= get(sumc[ch[p[u][i + 1].first]], dis);
	}
	return ret / 2 + 1;
}
void solve(int u, int fe)
{
	calc_size(u, -1);
	int m = INT_MAX;
	calc_focus(u, -1, sz[u], u, m);
	flag[u] = true;
	ch[u] = fe;
	calc_size(u, -1);
	sum[u].resize(sz[u]);
	sum[u][0] = 1;
	p[u].push_back(pii(u, 0));
	for (int x : g[u])
	{
		int v = e[x];
		if (check(v, -1))
		{
			sumc[x].resize(sz[v] + 1);
			get_nodes(v, u, 1, u, x);
			calc_sum(sumc[x]);
		}
	}
	calc_sum(sum[u]);
	for (int x : g[u])
	{
		int v = e[x];
		if (check(v, -1)) solve(v, x);
	}
}
int lca(int u, int v)
{
	if (dep[u] > dep[v]) swap(u, v);
	for (int i = dep[v] - dep[u], j = 0; i; i >>= 1, j++)
		if (i & 1) v = f[v][j];
	if (u == v) return u;
	for (int i = M - 1; i >= 0; i--)
		if (f[u][i] != f[v][i])
		{
			u = f[u][i];
			v = f[v][i];
		}
	return f[u][0];
}
void add_edge(int u, int v)
{
	g[u].push_back(e.size());
	e.push_back(v);
	g[v].push_back(e.size());
	e.push_back(u);
}
int proc_query()
{
	int k, ret = 0;
	scanf("%d", &k);
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &a[i]);
		a[i]--;
		scanf("%d", &r[a[i]]);
		r[a[i]] *= 2;
	}
	static auto cmp = [](int a, int b) { return id[a] < id[b]; };
	sort(a, a + k, cmp);
	int t = k;
	for (int i = 0; i < k - 1; i++) a[t++] = lca(a[i], a[i + 1]);
	a[t++] = 0;
	k = t;
	sort(a, a + k, cmp);
	k = unique(a, a + k) - a;
	for (int i = 1; i < k; i++)
	{
		int u = a[i], v = lca(a[i], a[i - 1]);
		vg[u].push_back(edge{ v,dep[u] - dep[v] });
		vg[v].push_back(edge{ u,dep[u] - dep[v] });
	}
	queue<int> q;
	for (int i = 0; i < k; i++)
		if (r[a[i]] > 0)
		{
			q.push(a[i]);
			inq[a[i]] = true;
		}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		inq[u] = false;
		for (int i = 0; i < vg[u].size(); i++)
		{
			int v = vg[u][i].to, d = vg[u][i].w;
			if (r[u] - d > r[v])
			{
				r[v] = r[u] - d;
				if (!inq[v])
				{
					inq[v] = true;
					q.push(v);
				}
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		int u = a[i];
		if (r[u] == -1) continue;
		ret += query(u, r[u]);
		for (int j = 0; j < vg[u].size(); j++)
		{
			int v = vg[u][j].to;
			if (dep[v] < dep[u] || dep[u] + r[u] < dep[v] - r[v]) continue;
			int x = (dep[u] + r[u] + dep[v] - r[v]) / 2;
			for (int i = dep[v] - x, j = 0; i; i >>= 1, j++)
				if (i & 1) v = f[v][j];
			ret -= query(v, dep[u] + r[u] - x);
		}
	}
	for (int i = 0; i < k; i++)
	{
		r[a[i]] = -1;
		vg[a[i]].clear();
	}
	return ret;
}
int main()
{
	memset(r, 0xff, sizeof r);
	int n;
	scanf("%d", &n);
	int t = n;
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(a - 1, t);
		add_edge(t, b - 1);
		t++;
	}
	dfs(0, 0);
	solve(0, -1);
	int q;
	scanf("%d", &q);
	while (q--) printf("%d\n", proc_query());
}
