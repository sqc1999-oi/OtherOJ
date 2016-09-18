#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>
using namespace std;
struct Edge
{
	int To, Pow;
	Edge(int to, int pow) :To(to), Pow(pow) {}
};
struct { int a, b, c; } debug[3601];
const int D[][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } }, INF = 0x3f3f3f3f;
int id[31][31][4], cnt = 0, d[31][31], n, m, q, map[32][32], dis[3601];
bool inq[3601];
vector<Edge> G[3601];
int bfs(int sx, int sy, int tx, int ty)
{
	if (sx == tx&&sy == ty) return 0;
	queue<pair<int, int> > q;
	q.push(make_pair(sx, sy));
	memset(d, 0x3f, sizeof d);
	d[sx][sy] = 0;
	while (!q.empty())
	{
		int ux = q.front().first, uy = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int vx = ux + D[i][0], vy = uy + D[i][1];
			if (map[vx][vy] && d[vx][vy] == INF)
			{
				d[vx][vy] = d[ux][uy] + 1;
				if (vx == tx&&vy == ty) return d[vx][vy];
				q.push(make_pair(vx, vy));
			}
		}
	}
	return INF;
}
int main()
{
	ifstream cin("PuzzleNOIP2013.in");
	ofstream cout("PuzzleNOIP2013.out");
	ios::sync_with_stdio(false);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				id[i][j][k] = ++cnt;
				debug[cnt].a = i;
				debug[cnt].b = j;
				debug[cnt].c = k;
			}
			cin >> map[i][j];
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (!map[i][j]) continue;
			map[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				if (!map[i + D[k][0]][j + D[k][1]]) continue;
				for (int l = 0; l < 4; l++)
				{
					if (!map[i + D[l][0]][j + D[l][1]]) continue;
					int x = bfs(i + D[k][0], j + D[k][1], i + D[l][0], j + D[l][1]) + 1;
					G[id[i][j][k]].push_back(Edge(id[i + D[l][0]][j + D[l][1]][(l + 2) % 4], x));
				}
			}
			map[i][j] = 1;
		}
	for (int i = 1; i <= q; i++)
	{
		int ex, ey, sx, sy, tx, ty;
		cin >> ex >> ey >> sx >> sy >> tx >> ty;
		if (!map[sx][sy])
		{
			cout << -1 << endl;
			continue;
		}
		if (sx == tx&&sy == ty)
		{
			cout << 0 << endl;
			continue;
		}
		memset(dis, 0x3f, sizeof dis);
		queue<int> q;
		map[sx][sy] = 0;
		for (int j = 0; j < 4; j++)
			if (map[sx + D[j][0]][sy + D[j][1]])
			{
				q.push(id[sx][sy][j]);
				inq[id[sx][sy][j]] = true;
				dis[id[sx][sy][j]] = bfs(ex, ey, sx + D[j][0], sy + D[j][1]);
			}
		map[sx][sy] = 1;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (int i = 0; i < G[u].size(); i++)
			{
				int v = G[u][i].To;
				int tmp = dis[v];
				dis[v] = min(dis[v], dis[u] + G[u][i].Pow);
				if (tmp != dis[v] && !inq[v])
				{
					q.push(v);
					inq[v] = true;
				}
			}
		}
		int ans = INF;
		for (int j = 0; j < 4; j++) ans = min(ans, dis[id[tx][ty][j]]);
		cout << (ans == INF ? -1 : ans) << endl;
	}
}
