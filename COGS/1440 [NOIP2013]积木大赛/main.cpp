#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
int main()
{
	ifstream cin("BlockNOIP2013.in");
	ofstream cout("BlockNOIP2013.out");
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int last = 0, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int now;
		cin >> now;
		if (now > last) ans += now - last;
		last = now;
	}
	cout << ans << endl;
}
