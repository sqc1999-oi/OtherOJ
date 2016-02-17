#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;
const int N = 5000000;
struct seg_node
{
	seg_node *l, *r;
	long long val;
} pool[N];
struct node_list_iterator
{
	vector<seg_node *> v;
	bool rev;
	long long get_left_val()
	{
		long long ret = 0;
		for (int i = 0; i < v.size(); i++) ret += (rev ? v[i]->r : v[i]->l)->val;
		return ret;
	}
	void move_left()
	{
		for (int i = 0; i < v.size(); i++)
			v[i] = (rev ? v[i]->r : v[i]->l);
	}
	void move_right()
	{
		for (int i = 0; i < v.size(); i++)
			v[i] = (rev ? v[i]->l : v[i]->r);
	}
};
seg_node *new_node()
{
	static int cnt = 0;
	assert(cnt < N);
	return &pool[cnt++];
}
int lowbit(int x) { return x&-x; }
void update(int k, int x, int *t, int n)
{
	while (k <= n)
	{
		t[k] += x;
		k += lowbit(k);
	}
}
long long query(int k, int *t)
{
	long long ret = 0;
	while (k > 0)
	{
		ret += t[k];
		k -= lowbit(k);
	}
	return ret;
}
seg_node *update(seg_node *x, int l, int r, int k, long long val)
{
	if (x->val == 0)
	{
		seg_node *tmp = new_node();
		memcpy(tmp, x, sizeof(seg_node));
		x = tmp;
	}
	x->val += val;
	if (k < (l + r) / 2) x->l = update(x->l, l, (l + r) / 2, k, val);
	else x->r = update(x->r, (l + r) / 2, r, k, val);
	return x;
}
void update(int k, int x, seg_node **t, int n)
{
	while (k <= n)
	{
		t[k] = update(t[k], 0, n, k, x);
		k += lowbit(k);
	}
}
void init_iterator(node_list_iterator &it, int k, seg_node **t)
{
	while (k > 0)
	{
		it.v.push_back(t[k]);
		k -= lowbit(k);
	}
}
long long query(int tl, int tr, int k, seg_node **t, int n, bool flag)
{
	node_list_iterator il, ir;
	init_iterator(il, tl - 1, t);
	init_iterator(ir, tr, t);
	il.rev = ir.rev = flag;
	int l = 0, r = n;
	long long ret = 0;
	while (l != r - 1)
	{
		if ((k < (l + r) / 2) ^ flag ^ 1)
		{
			il.move_left();
			ir.move_left();
			(flag ? l : r) = (l + r) / 2;
		}
		else
		{
			ret += ir.get_left_val() - il.get_left_val();
			il.move_right();
			ir.move_right();
			(flag ? r : l) = (l + r) / 2;
		}
	}
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	int *a = new int[n], *t = new int[n + 1], *p = new int[n];
	long long ans = 0, *f = new long long[n], *b = new long long[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		ans += b[i] = query(n, t) - query(a[i], t);
		update(a[i], 1, t, n);
		a[i]--;
		p[a[i]] = i;
	}
	memset(t, 0x00, sizeof t);
	for (int i = n - 1; i >= 0; i--)
	{
		f[i] = query(a[i], t);
		update(a[i] + 1, 1, t, n);
	}
	delete[] t;
	seg_node **st = new seg_node *[n + 1];
	for (int i = 0; i < m; i++)
	{
		int x;
		cin >> x;

	}
}