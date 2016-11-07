#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int P = 1e5;
int pow(int a, int b, int p)
{
	long long ret = 1, t = a;
	while (b > 0)
	{
		if (b & 1) (ret *= t) %= p;
		(t *= t) %= p;
		b >>= 1;
	}
	return ret;
}
int calc(int n, int p, int c, int &cnt)
{
	int P = 1;
	for (int i = 1; i <= c; i++) P *= p;
	long long ret = 1;
	if (n < p)
	{
		for (int i = 1; i <= n; i++) (ret *= i) %= P;
		cnt = 0;
	}
	else
	{
		(ret *= calc(n / p, p, c, cnt)) %= P;
		cnt += n / p;
		long long t = 1;
		for (int i = 1; i <= P; i++)
			if (i%p != 0) (t *= i) %= P;
		(ret *= pow(t, n / P, P)) %= P;
		for (int i = 1; i <= n%P; i++)
			if (i%p != 0) (ret *= i) %= P;
	}
	return ret;
}
int exgcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int ret = exgcd(b, a%b, y, x);
	y -= x*(a / b);
	return ret;
}
int inv(int a, int p)
{
	int x, y;
	exgcd(a, p, x, y);
	return (x%p + p) % p;
}
int crt(int n, const vector<int> &v, const vector<int> &p)
{
	int m = 1;
	long long ret = 0;
	for (int i = 0; i < n; i++) m *= p[i];
	for (int i = 0; i < n; i++)
	{
		int _m = m / p[i];
		ret = (ret + v[i] * _m % m * inv(_m, p[i]) % m) % m;
	}
	return ret;
}
int derange(int n, int p)
{
	static int h[P * 2];
	h[0] = 1;
	h[1] = 0;
	for (int i = 2; i < p * 2; i++)
		h[i] = ((long long)i*h[i - 1] + (i & 1 ? p - 1 : 1)) % p;
	return h[n % (p * 2)];
}
int choose(int n, int m, int p)
{
	vector<int> v, vp;
	for (int i = 2; i <= p; i++)
		if (p%i == 0)
		{
			int e = 0, _p = 1;
			do
			{
				e++;
				p /= i;
				_p *= i;
			} while (p%i == 0);
			int cnt1, cnt2, cnt3;
			long long t = calc(n, i, e, cnt1);
			(t *= inv(calc(m, i, e, cnt2), _p)) %= _p;
			(t *= inv(calc(n - m, i, e, cnt3), _p)) %= _p;
			(t *= pow(i, cnt1 - cnt2 - cnt3, _p)) %= _p;
			v.push_back(t);
			vp.push_back(_p);
		}
	return crt(v.size(), v, vp);
}
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		int n, k, m;
		cin >> n >> k >> m;
		cout << "Case " << i << ": ";
		if (m == 1) cout << 0 <<endl;
		else cout << (long long)derange(n - k, m)*choose(n, k, m) % m << endl;
	}
}
