#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
struct Edge
{
	int To;
	long long Pow;
	Edge(int to, long long pow) :To(to), Pow(pow) {}
	bool operator <(const Edge &b) const { return Pow < b.Pow; }
};
vector<Edge> G[50001];
int pos[50001], f[50001][17], bra[50001];
long long d[50001][17];
bool ctrl[50001];
void update_dfs(int u, int fa)
{
	bool flag = ctrl[u];
	if (!flag) ctrl[u] = G[u].size() > 1 ? true : false;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].To;
		if (v != fa)
		{
			update_dfs(v, u);
			if (!flag) ctrl[u] &= ctrl[v];
		}
	}
}
void pret_dfs(int u, int fa)
{
	f[u][0] = fa;
	for (int i = 1; i <= 16; i++)
	{
		f[u][i] = f[f[u][i - 1]][i - 1];
		if (f[u][i] != 0) d[u][i] = d[u][i - 1] + d[f[u][i - 1]][i - 1];
	}
	if (u != 1 && bra[u] == 0) bra[u] = bra[fa];
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].To;
		if (v != fa)
		{
			if (u == 1) bra[v] = v;
			d[v][0] = G[u][i].Pow;
			pret_dfs(v, u);
		}
	}
}
bool check(long long limit, int n, int m)
{
	memset(ctrl, 0x00, sizeof ctrl);
	vector<pair<long long, int> > a, b, t;
	for (int i = 1; i <= m; i++)
	{
		int s = pos[i];
		long long tmp = limit;
		for (int j = 16; j >= 0; j--)
		{
			if (f[s][j] != 0 && d[s][j] <= tmp)
			{
				tmp -= d[s][j];
				s = f[s][j];
			}
		}
		if (s == 1) t.push_back(make_pair(tmp, i));
		else ctrl[s] = true;
	}
	update_dfs(1, 0);
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i].first < d[bra[pos[t[i].second]]][0] && !ctrl[bra[pos[t[i].second]]])
			ctrl[bra[pos[t[i].second]]] = true;
		else a.push_back(t[i]);
	}
	for (int i = 0; i < G[1].size(); i++)
		if (!ctrl[G[1][i].To]) b.push_back(make_pair(G[1][i].Pow, G[1][i].To));
	sort(a.begin(), a.end());
	int i = 0, j = 0, cnt = 0;
	while (i < a.size() && j < b.size())
	{
		if (!ctrl[bra[pos[a[i].second]]])
		{
			ctrl[bra[pos[a[i].second]]] = true;
			i++;
			cnt++;
		}
		else if (ctrl[b[j].second])
		{
			j++;
			cnt--;
		}
		else if (a[i].first >= b[j].first)
		{
			ctrl[b[j].second] = true;
			i++;
			j++;
		}
		else i++;
	}
	return j + cnt == b.size();
}
int main()
{
	ifstream cin("blockade.in");
	ofstream cout("blockade.out");
	ios::sync_with_stdio(false);
	int n;
	long long l = 0, r = 0, ans = -1;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		G[u].push_back(Edge(v, w));
		G[v].push_back(Edge(u, w));
		r += w;
	}
	pret_dfs(1, 0);
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> pos[i];
	sort(G[1].begin(), G[1].end());
	while (l <= r)
	{
		long long mid = (l + r) / 2;
		if (check(mid, n, m))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans << endl;
}
