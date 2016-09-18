#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
const int P[] = { 10007,11261,14843,19997,21893 };
int a[101][5], f[21893][5];
int main()
{
	ifstream cin("equationa.in");
	ofstream cout("equationa.out");
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i <= n; i++)
	{
		string s;
		cin >> s;
		bool flag = false;
		if (s[0] == '-') flag = true, s[0] = '0';
		for (int j = 0; j < s.length(); j++)
		{
			for (int k = 0; k < 5; k++)
			{
				((a[i][k] *= 10) += s[j] - '0') %= P[k];
			}
		}
		if (flag)
			for (int j = 0; j < 5; j++) a[i][j] = P[j] - a[i][j];
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < P[i]; j++)
		{
			int x = 1;
			for (int k = 0; k <= n; k++)
			{
				(f[j][i] += a[k][i] * x) %= P[i];
				(x *= j) %= P[i];
			}
		}
	}
	vector<int> ans;
	for (int i = 1; i <= m; i++)
	{
		bool flag = true;
		for (int j = 0; j < 5; j++) if (f[i%P[j]][j] != 0)
		{
			flag = false;
			break;
		}
		if (flag) ans.push_back(i);
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) cout << ans[i] << endl;
}
