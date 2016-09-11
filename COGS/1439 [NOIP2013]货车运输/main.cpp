#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
struct Edge { int From, To, Pow; } e[50001];
int p[10001], r[10001], d[10001], w[10001];
vector<int> G[10001];
bool cmp(const Edge &a, const Edge &b) { return a.Pow > b.Pow; }
int find(int x) { return x == p[x] ? x : find(p[x]); }
void dfs(int u)
{
	d[u] = d[p[u]] + 1;
	for (int i = 0; i < G[u].size(); i++) dfs(G[u][i]);
}
int main()
{
	ifstream cin("truck.in");
	ofstream cout("truck.out");
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> e[i].From >> e[i].To >> e[i].Pow;
	sort(e + 1, e + 1 + m, cmp);
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int x = find(e[i].From), y = find(e[i].To);
		if (x != y)
		{
			if (r[x] > r[y])
			{
				p[y] = x;
				r[x] = max(r[x], r[y] + 1);
				w[y] = e[i].Pow;
				G[x].push_back(y);
			}
			else
			{
				p[x] = y;
				r[y] = max(r[y], r[x] + 1);
				w[x] = e[i].Pow;
				G[y].push_back(x);
			}
		}
	}
	for (int i = 1; i <= n; i++) if (p[i] == i) dfs(i);
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		int x, y;
		cin >> x >> y;
		if (x == y)
		{
			cout << 0 << endl;
			continue;
		}
		if (d[y] > d[x]) swap(x, y);
		int ans = 0x7fffffff;
		while (d[x] > d[y])
		{
			ans = min(ans, w[x]);
			x = p[x];
		}
		while (x != y)
		{
			ans = min(ans, min(w[x], w[y]));
			if (p[x] == x)
			{
				ans = -1;
				break;
			}
			x = p[x];
			y = p[y];
		}
		cout << ans << endl;
	}
}
