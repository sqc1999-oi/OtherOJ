#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
typedef pair<long long, long long> pll;
struct city
{
	long long h;
	int id;
	bool operator <(const city &b) const { return h < b.h; }
} a[100001];
int f[100001][19], I;
long long dis[100001][19][2];
bool cmp(const city &x, const city &y)
{
	long long xx = abs(x.h - a[I].h), yy = abs(y.h - a[I].h);
	return xx < yy || (xx == yy&&x.h < y.h);
}
pll solve(int s, long long x)
{
	pll ans;
	for (int i = 17; i >= 0; i--)
	{
		if (f[s][i] != 0 && dis[s][i][0] + dis[s][i][1] <= x)
		{
			x -= dis[s][i][0] + dis[s][i][1];
			ans.first += dis[s][i][0];
			ans.second += dis[s][i][1];
			s = f[s][i];
		}
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	ifstream cin("drive.in");
	ofstream cout("drive.out");
	int n;
	cin >> n;
	set<city> s;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].h;
		a[i].id = i;
		s.insert(a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		set<city>::iterator it = s.find(a[i]), forward, backward;
		backward = forward = it;
		vector<city> v;
		if (forward != s.end())
		{
			forward++;
			for (int j = 1; j <= 2 && forward != s.end(); j++, forward++)
				v.push_back(*forward);
		}
		if (backward != s.begin() && backward != s.end())
		{
			backward--;
			for (int j = 1; j <= 2 && backward != s.end(); j++, backward--)
			{
				v.push_back(*backward);
				if (backward == s.begin()) break;
			}
		}
		I = i;
		sort(v.begin(), v.end(), cmp);
		if (v.size() > 0)
		{
			f[i][18] = v[0].id;
			dis[i][18][1] = abs(a[i].h - v[0].h);
		}
		if (v.size() > 1)
		{
			f[i][0] = v[1].id;
			dis[i][0][0] = abs(a[i].h - v[1].h);
		}
		s.erase(it);
	}
	for (int j = 1; j <= 17; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			int k = j == 1 ? 18 : (j - 1);
			int a = f[i][j - 1];
			int b = f[a][k];
			if (a*b != 0)
			{
				f[i][j] = b;
				dis[i][j][0] = dis[i][j - 1][0] + dis[a][k][0];
				dis[i][j][1] = dis[i][j - 1][1] + dis[a][k][1];
			}
		}
	}
	long long x0;
	cin >> x0;
	pll ans(1, 0);
	int pos = 0;
	for (int i = 1; i <= n; i++)
	{
		pll tmp = solve(i, x0);
		if (tmp.first + tmp.second != 0)
		{
			long long x = tmp.first*ans.second, y = tmp.second*ans.first;
			if (x < y || (x == y&&a[i].h > a[pos].h))
			{
				ans = tmp;
				pos = i;
			}
		}
	}
	cout << pos << endl;
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int s;
		long long x;
		cin >> s >> x;
		pll tmp = solve(s, x);
		cout << tmp.first << ' ' << tmp.second << endl;
	}
}