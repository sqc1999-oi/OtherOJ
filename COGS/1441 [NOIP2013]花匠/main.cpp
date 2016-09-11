#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
using namespace std;
inline void push(stack<int> &s, int x, int flag)
{
	if (s.empty()) s.push(x);
	else if (x != s.top())
	{
		if (s.size() % 2 == 1)
		{
			if ((x > s.top()) ^ flag) s.push(x);
			else
			{
				s.pop();
				s.push(x);
			}
		}
		else
		{
			if ((x < s.top()) ^ flag) s.push(x);
			else
			{
				s.pop();
				s.push(x);
			}
		}
	}
}
int main()
{
	ifstream cin("FlowerNOIP2013.in");
	ofstream cout("FlowerNOIP2013.out");
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	stack<int> s1, s2;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		push(s1, x, 0);
		push(s2, x, 1);
	}
	cout << max(s1.size(), s2.size());
}
