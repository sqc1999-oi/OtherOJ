#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>
using namespace std;
vector<int> G[10001], rG[10001];
bool vis[10001], inq[10001];
int dis[10001], out[10001];
void dfs(int u)
{
	if (vis[u]) return;
	vis[u] = true;
	for (int i = 0; i < rG[u].size(); i++) dfs(rG[u][i]), out[rG[u][i]]--;
}
int Spfa(int s, int t)
{
	queue<int> q;
	q.push(s);
	memset(dis, 0x7f, sizeof dis);
	dis[s] = 0;
	inq[s] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		inq[u] = false;
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if (out[v]) continue;
			int tmp = dis[v];
			dis[v] = min(dis[v], dis[u] + 1);
			if (tmp != dis[v] && !inq[v])
			{
				q.push(v);
				inq[v] = true;
			}
		}
	}
	return dis[t] == 0x7f7f7f7f ? -1 : dis[t];
}
int main()
{
	ifstream cin("roadb.in");
	ofstream cout("roadb.out");
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
		rG[y].push_back(x);
		out[x]++;
	}
	int s, t;
	cin >> s >> t;
	dfs(t);
	cout << Spfa(s, t) << endl;
}
