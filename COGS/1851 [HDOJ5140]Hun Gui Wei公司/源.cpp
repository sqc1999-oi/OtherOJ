#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cassert>
#include <cstdarg>
using namespace std;
const int N = 4e6;
struct seg_node
{
	seg_node *l, *r;
	long long val;
} pool[N];
struct d
{
	long long s, l, a;
	bool operator <(const d &b) const { return l < b.l; }
};
seg_node *new_node()
{
	static int cnt = 0;
	assert(cnt < N);
	return &pool[cnt++];
}
seg_node *update(seg_node *n, int l, int r, int k, long long val)
{
	seg_node *x = new_node();
	memcpy(x, n, sizeof(seg_node));
	x->val += val;
	if (l != r - 1)
		if (k < (l + r) / 2) x->l = update(x->l, l, (l + r) / 2, k, val);
		else x->r = update(x->r, (l + r) / 2, r, k, val);
	return x;
}
long long query(seg_node *x, int l, int r, int ql, int qr)
{
	if (ql == l&&qr == r || x->val == 0) return x->val;
	if (qr < (l + r) / 2) return query(x->l, l, (l + r) / 2, ql, qr);
	if (ql > (l + r) / 2) return query(x->r, (l + r) / 2, r, ql, qr);
	return query(x->l, l, (l + r) / 2, ql, (l + r) / 2) + query(x->r, (l + r) / 2, r, (l + r) / 2, qr);
}
void _delete(int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--) delete[] va_arg(li, void *);
	va_end(li);
}
int main()
{
#ifndef DEBUG
	ifstream cin("hunguiwei.in");
	ofstream cout("hunguiwei.out");
#endif
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n)
	{
		d* a = new d[n];
		long long *b = new long long[n], *c = new long long[n];
		for (int i = 0; i < n; i++)
		{
			cin >> a[i].s >> a[i].l >> a[i].a;
			b[i] = a[i].l;
			c[i] = a[i].a;
		}
		sort(a, a + n);
		sort(b, b + n);
		sort(c, c + n);
		long long *e = unique(c, c + n);
		seg_node **rt = new seg_node*[n + 1];
		rt[0] = new_node();
		rt[0]->l = rt[0]->r = rt[0];
		rt[0]->val = 0;
		for (int i = 0; i < n; i++)
			rt[i + 1] = update(rt[i], 0, e - c, lower_bound(c, e, a[i].a) - c, a[i].s);
		int m;
		cin >> m;
		long long last = 0;
		for (int i = 0; i < m; i++)
		{
			long long ll, hl, la, ha;
			cin >> ll >> hl >> la >> ha;
			ll += last, hl -= last, la += last, ha -= last;
			if (ll > hl) swap(ll, hl);
			if (la > ha) swap(la, ha);
			ll = lower_bound(b, b + n, ll) - b;
			hl = upper_bound(b, b + n, hl) - b;
			la = lower_bound(c, e, la) - c;
			ha = upper_bound(c, e, ha) - c;
			last = query(rt[hl], 0, e - c, la, ha) - query(rt[ll], 0, e - c, la, ha);
			cout << last << endl;
		}
		_delete(4, a, b, c, rt);
	}
}