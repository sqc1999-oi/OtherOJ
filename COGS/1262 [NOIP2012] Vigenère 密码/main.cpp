#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;
int main()
{
	ifstream cin("vigenere.in");
	ofstream cout("vigenere.out");
	ios::sync_with_stdio(false);
	string k, s;
	cin >> k >> s;
	while (k.length() < s.length()) k += k;
	for (int i = 0; i < s.length(); i++)
	{
		char a;
		if (isupper(s[i]))
		{
			a = 'A';
			k[i] = toupper(k[i]);
		}
		else
		{
			a = 'a';
			k[i] = tolower(k[i]);
		}
		char x = (s[i] - k[i] + a);
		if (x < a) x += 26;
		s[i] = x;
	}
	cout << s << endl;
}
