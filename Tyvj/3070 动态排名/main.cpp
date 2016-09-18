#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <vector>
#include <cstdarg>
#include <cctype>
using namespace std;
const int N = 4000000;
struct seg_node
{
	seg_node *l, *r;
	int val;
} pool[N];
struct node_list_iterator
{
	vector<seg_node *> v;
	void move_left() { for (int i = 0; i < v.size(); i++) v[i] = v[i]->l; }
	void move_right() { for (int i = 0; i < v.size(); i++) v[i] = v[i]->r; }
	int get_left_val()
	{
		int ret = 0;
		for (int i = 0; i < v.size(); i++) ret += v[i]->l->val;
		return ret;
	}
};
int cnt;
seg_node *new_node()
{
	assert(cnt < N);
	return &pool[cnt++];
}
seg_node *seg_update(seg_node *x, int l, int r, int k, int val)
{
	if (x->val == 0)
	{
		seg_node *tmp = new_node();
		memcpy(tmp, x, sizeof(seg_node));
		x = tmp;
	}
	x->val += val;
	if (l != r - 1)
		if (k < (l + r) / 2) x->l = seg_update(x->l, l, (l + r) / 2, k, val);
		else x->r = seg_update(x->r, (l + r) / 2, r, k, val);
		return x;
}
int lowbit(int x) { return x&-x; }
void update(int x, int k, int val, seg_node **t, int n, int m)
{
	while (x <= n)
	{
		t[x] = seg_update(t[x], 0, m, k, val);
		x += lowbit(x);
	}
}
void init_iterator(node_list_iterator &it, int x, seg_node **t)
{
	while (x > 0)
	{
		it.v.push_back(t[x]);
		x -= lowbit(x);
	}
}
int query(int sl, int sr, int k, seg_node **t, int m)
{
	node_list_iterator il, ir;
	init_iterator(il, sl - 1, t);
	init_iterator(ir, sr, t);
	int l = 0, r = m;
	while (l != r - 1)
	{
		int val = ir.get_left_val() - il.get_left_val();
		if (k <= val)
		{
			il.move_left();
			ir.move_left();
			r = (l + r) / 2;
		}
		else
		{
			k -= val;
			il.move_right();
			ir.move_right();
			l = (l + r) / 2;
		}
	}
	return l;
}
void read(FILE *f, int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--)
	{
		int &x = *va_arg(li, int *), ch;
		x = 0;
		do ch = getc(f);
		while (!isdigit(ch));
		do
		{
			(x *= 10) += ch - '0';
			ch = getc(f);
		} while (isdigit(ch));
	}
}
int nextch(FILE *f)
{
	int ret;
	do ret = getc(f);
	while (ret == ' ' || ret == '\r' || ret == '\n');
	return ret;
}
int main()
{
	FILE *in = stdin, *out = stdout;
	int T;
	read(in, 1, &T);
	while (T--)
	{
		cnt = 0;
		int n, m;
		read(in, 2, &n, &m);
		seg_node **t = new seg_node *[n + 1], *nul = new_node();
		nul->l = nul->r = nul;
		nul->val = 0;
		for (int i = 1; i <= n; i++) t[i] = nul;
		char *op = new char[m];
		int *a = new int[n], *x = new int[m], *y = new int[m], *z = new int[m];
		vector<int> b;
		for (int i = 0; i < n; i++)
		{
			read(in, 1, &a[i]);
			b.push_back(a[i]);
		}
		for (int i = 0; i < m; i++)
		{
			op[i] = nextch(in);
			read(in, 2, &x[i], &y[i]);
			if (op[i] == 'Q') read(in, 1, &z[i]);
			else if (op[i] == 'C') b.push_back(y[i]);
		}
		sort(b.begin(), b.end());
		b.resize(unique(b.begin(), b.end()) - b.begin());
		for (int i = 0; i < n; i++)
		{
			a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
			update(i + 1, a[i], 1, t, n, b.size());
		}
		for (int i = 0; i < m; i++)
		{
			if (op[i] == 'Q')
				fprintf(out, "%d\n", b[query(x[i], y[i], z[i], t, b.size())]);
			else if (op[i] == 'C')
			{
				y[i] = lower_bound(b.begin(), b.end(), y[i]) - b.begin();
				update(x[i], a[x[i] - 1], -1, t, n, b.size());
				update(x[i], y[i], 1, t, n, b.size());
				a[x[i] - 1] = y[i];
			}
		}
		delete[] t, op, a, x, y, z;
	}
}
