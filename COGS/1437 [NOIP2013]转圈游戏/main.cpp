#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
int pow(int a, int b, int p)
{
	int ans = 1;
	for (; b; b >>= 1, (a *= a) %= p)
		if (b & 1) (ans *= a) %= p;
	return ans;
}
int main()
{
	ifstream cin("CircleNOIP2013.in");
	ofstream cout("CircleNOIP2013.out");
	ios::sync_with_stdio(false);
	int n, m, k, x;
	cin >> n >> m >> k >> x;
	cout << (x + m*pow(10, k, n)) % n << endl;
}
