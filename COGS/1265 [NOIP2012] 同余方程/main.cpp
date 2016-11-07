#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
int exgcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return b;
	}
	int tmp = exgcd(b, a%b, y, x);
	y -= x*(a / b);
	return tmp;
}
int main()
{
	ifstream cin("mod.in");
	ofstream cout("mod.out");
	ios::sync_with_stdio(false);
	int a, b;
	cin >> a >> b;
	int x, y;
	int g = exgcd(a, b, x, y);
	cout << (x + b) % b;
}
