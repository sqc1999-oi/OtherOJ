#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
vector<int> G[200001];
int sum[200001], max1[200001], max2[200001], w[200001], Sum, Max;
void dfs(int u, int fa)
{
	if (fa != 0)
	{
		(Sum += w[u] * (sum[fa] - w[u])) %= 10007;
		Max = max(Max, (max1[fa] != w[u] ? max1[fa] : max2[fa])*w[u]);
	}
	for (int i = 0; i < G[u].size(); i++)
	{
		int x = w[G[u][i]];
		(sum[u] += x*(G[u][i] == fa ? 2 : 1)) %= 10007;
		if (x > max1[u]) max2[u] = max(max2[u], max1[u]), max1[u] = x;
		else if (x > max2[u]) max2[u] = x;
	}
	for (int i = 0; i < G[u].size(); i++) if (G[u][i] != fa) dfs(G[u][i], u);
}
int main()
{
	ifstream cin("linkb.in");
	ofstream cout("linkb.out");
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) cin >> w[i];
	dfs(1, 0);
	cout << Max << ' ' << Sum << endl;
}
