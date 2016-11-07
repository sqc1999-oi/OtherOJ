#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
vector<int> G[200000];
int dis[200000], flag[200000], cnt;
int bfs(int s)
{
	cnt++;
	int ret = INT_MAX;
	queue<int> q;
	q.push(s);
	dis[s] = 1;
	flag[s] = cnt;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if (dis[v] == 0)
			{
				dis[v] = dis[u] + 1;
				q.push(v);
				flag[v] = cnt;
			}
			else if (flag[v] == cnt) ret = min(ret, dis[u] - dis[v] + 1);
		}
	}
	return ret;
}
int main()
{
	freopen("2015message.in", "r", stdin);
	freopen("2015message.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int t;
		scanf("%d", &t);
		G[i].push_back(t - 1);
	}
	int ans = INT_MAX;
	for (int i = 0; i < n; i++)
		if (dis[i] == 0)
			ans = min(ans, bfs(i));
	printf("%d", ans);
}
