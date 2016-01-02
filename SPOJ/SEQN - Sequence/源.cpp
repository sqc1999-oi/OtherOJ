#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>

typedef long long ll;

const int M = 100005;  
const int N = 405;

int p[N], e[N], len, cover[N], pri[N], top, f[M], finv[M], b[N], w[N], num[M * 2], pi, pi_e, n, k, m, cas = 1;
ll cnt_of_p;

void prim();
void init();
void sol();
int cal_num();
int cal_c();
void get_f_inv();
int cal_inv(int k);
void ext_gcd(int aa, int bb, int & x, int & y);
int cal_f(int n);
int cal_finv(int n);
int mul_mod(ll a, int k, int p);
int CRT();

int main()
{
	int t;
	scanf("%d", &t);
	prim();
	while (t--)
	{
		init();
		sol();
	}
}

void prim()
{
	top = 0;
	memset(cover, 0, sizeof(cover));
	for (int i = 2; i < N; i++)
	{
		if (cover[i] == 0) pri[top++] = i;
		for (int j = 0; j < top && i * pri[j] < N; j++)
		{
			pri[i*pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

void init()
{
	int tm;
	scanf("%d%d%d", &n, &k, &m);

	tm = m;
	len = 0;
	for (int i = 0; i < top && pri[i] <= tm; i++)
	{
		if (tm % pri[i] == 0)
		{
			p[len] = pri[i];    
			e[len] = 0;    
			w[len] = 1;    
			while (tm %pri[i] == 0)  
			{
				e[len]++;
				tm /= pri[i];
				w[len] *= pri[i];
			}
			len++;
		}
	}
	if (tm > 1)
	{
		p[len] = tm;
		w[len] = tm;
		e[len++] = 1;
	}
	return;
}

void sol()
{
	ll res;
	if (m == 1)
	{
		printf("Case %d: 0\n", cas++);
		return;
	}
	if (k == n)
	{
		printf("Case %d: 1\n", cas++);
		return;
	}
	if (k == n - 1)
	{
		printf("Case %d: 0\n", cas++);
		return;
	}

	res = cal_num();    
	res *= cal_c();
	res %= m;
	printf("Case %d: %I64d\n", cas++, res);
	return;
}

int cal_num()
{
	int lofseg, rem;
	num[0] = 1;
	num[1] = 0;
	lofseg = 0;
	for (int i = 2;; i++)
	{
		num[i] = (ll)(i - 1)*(num[i - 1] + num[i - 2]) % m;
		if (num[i] == 0 && i % m == 1 && num[i - 1] == 1)
		{
			lofseg = i - 1;    
			break;
		}
	}
	rem = (n - k) % lofseg;
	return num[rem];
}

int cal_c()
{
	int ans;
	for (int i = 0; i < len; i++)
	{
		pi = p[i];
		pi_e = w[i];
		cnt_of_p = 0;
		get_f_inv();
		b[i] = cal_f(n);
		b[i] *= cal_finv(k); b[i] %= pi_e;
		b[i] *= cal_finv(n - k); b[i] %= pi_e;
		b[i] *= mul_mod(pi, cnt_of_p, pi_e); b[i] %= pi_e;
	}
	ans = CRT();
	return ans;
}

void get_f_inv()
{
	f[0] = finv[0] = f[1] = finv[1] = 1;
	cnt_of_p = 0;
	for (int i = 2; i < pi_e; i++)
	{
		f[i] = f[i - 1];
		finv[i] = finv[i - 1];
		if (i % pi)
		{
			f[i] = f[i] * i % m;
			finv[i] = finv[i] * cal_inv(i) % m;
		}
	}
	return;
}

int cal_inv(int k)
{
	int x, y;
	ext_gcd(k, pi_e, x, y);
	while (x <0)x += pi_e;
	return x;
}

void ext_gcd(int aa, int bb, int & x, int &y)
{
	if (bb == 0)
	{
		x = 1;
		y = 0;
		return;
	}

	int tx;
	ext_gcd(bb, aa % bb, x, y);
	tx = x;
	x = y;
	y = tx - aa / bb * y;
	return;
}

int cal_f(int n)
{
	if (n <= 1)return 1;
	int cnt_of_seg = n / pi_e, rem = n % pi_e, ans;
	ans = mul_mod(f[pi_e - 1], cnt_of_seg, pi_e);
	ans *= f[rem];
	ans %= pi_e;
	n /= pi;
	cnt_of_p += n;
	ans *= cal_f(n);
	ans %= pi_e;
	return ans;
}

int cal_finv(int n)
{
	if (n <= 1) return 1;
	ll cnt_of_seg = n / pi_e, rem = n % pi_e, ans;
	ans = mul_mod(finv[pi_e - 1], cnt_of_seg, pi_e);
	ans *= finv[rem];
	ans %= pi_e;
	n /= pi;
	cnt_of_p -= n;
	ans *= cal_finv(n);
	ans %= pi_e;
	return ans;
}

int mul_mod(ll a, int k, int p)
{
	ll ans = 1, tmp = a%p;
	while (k)
	{
		if (k & 1)ans = (ans*tmp) % p;
		tmp = (tmp*tmp) % p;
		k >>= 1;
	}
	return ans;
}

int CRT()
{
	int x, y, ans = 0, m, n = 1;
	for (int i = 0; i < len; i++) n *= w[i];
	for (int i = 0; i < len; i++)
	{
		m = n / w[i];
		ext_gcd(w[i], m, x, y);
		ll ty = y;
		ty = ty*m%n;
		ty = ty * b[i] % n;
		ans = (ans + ty) % n;
	}
	if (ans >= 0)return ans;
	return ans + n;
}
