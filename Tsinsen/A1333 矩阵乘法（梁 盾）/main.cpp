#include <cstdio>
#include <cstdarg>
#include <cctype>
#include <algorithm>
using namespace std;
void read(int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--)
	{
		int &x = *va_arg(li, int *), ch;
		x = 0;
		do ch = getchar();
		while (!isdigit(ch));
		do
		{
			x = x * 10 + ch - '0';
			ch = getchar();
		} while (isdigit(ch));
	}
	va_end(li);
}
const int N = 500, Q = 6e4;
int ans[Q];
struct cell
{
	int x, y, v;
	bool operator <(const cell &b) const { return v < b.v; }
} a[N*N];
struct query
{
	int x1, y1, x2, y2, v, id;
} q[Q], t1[Q], t2[Q];
namespace bit
{
	int t[N + 1][N + 1];
	int lowbit(int x) { return x&-x; }
	void update(int x, int y, int v)
	{
		for (; x <= N; x += lowbit(x))
			for (int i = y; i <= N; i += lowbit(i))
				t[x][i] += v;
	}
	int query(int x, int y)
	{
		int ans = 0;
		for (; x > 0; x -= lowbit(x))
			for (int i = y; i > 0; i -= lowbit(i))
				ans += t[x][i];
		return ans;
	}
}
void solve(int l, int r, int ul, int ur, int ql, int qr)
{
	if (ql == qr) return;
	if (l == r - 1)
	{
		for (int i = ql; i < qr; i++) ans[q[i].id] = l;
		return;
	}
	int mid = (l + r) / 2, umid;
	for (umid = ul; umid < ur&&a[umid].v < mid; umid++)
		bit::update(a[umid].x, a[umid].y, 1);
	int cnt = 0;
	for (int i = ql; i < qr; i++)
	{
		int x = bit::query(q[i].x2, q[i].y2)
			- bit::query(q[i].x1 - 1, q[i].y2)
			- bit::query(q[i].x2, q[i].y1 - 1)
			+ bit::query(q[i].x1 - 1, q[i].y1 - 1);
		if (x >= q[i].v) t1[cnt++] = q[i];
		else
		{
			q[i].v -= x;
			t2[i - ql - cnt] = q[i];
		}
	}
	for (int i = ul; i < umid; i++) bit::update(a[i].x, a[i].y, -1);
	for (int i = 0; i < cnt; i++) q[ql + i] = t1[i];
	for (int i = 0; i < qr - ql - cnt; i++) q[ql + cnt + i] = t2[i];
	solve(l, mid, ul, umid, ql, ql + cnt);
	solve(mid, r, umid, ur, ql + cnt, qr);
}
int main()
{
	int n, m, max = 0, min = 1e9;
	read(2, &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			a[i*n + j].x = i + 1;
			a[i*n + j].y = j + 1;
			read(1, &a[i*n + j].v);
			max = ::max(max, a[i*n + j].v);
			min = ::min(min, a[i*n + j].v);
		}
	for (int i = 0; i < m; i++)
	{
		q[i].id = i;
		read(5, &q[i].x1, &q[i].y1, &q[i].x2, &q[i].y2, &q[i].v);
	}
	sort(a, a + n*n);
	solve(min, max + 1, 0, n*n, 0, m);
	for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
}
