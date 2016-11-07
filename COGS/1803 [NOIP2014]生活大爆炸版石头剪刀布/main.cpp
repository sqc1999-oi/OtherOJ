#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
const int TABLE[][5] = { { 0,0,1,1,0 },{ 1,0,0,1,0 },{ 0,1,0,0,1 },{ 0,0,1,0,1 },{ 1,1,0,0,0 } };
int a[200], b[200];
int main()
{
	ifstream cin("rps.in");
	ofstream cout("rps.out");
	ios::sync_with_stdio(false);
	int n, na, nb;
	cin >> n >> na >> nb;
	for (int i = 0; i < na; i++) cin >> a[i];
	for (int i = 0; i < nb; i++) cin >> b[i];
	int ansa = 0, ansb = 0;
	for (int i = 1, j = 0, k = 0; i <= n; ++i, (++j) %= na, (++k) %= nb)
	{
		ansa += TABLE[a[j]][b[k]];
		ansb += TABLE[b[k]][a[j]];
	}
	cout << ansa << ' ' << ansb << endl;
}
