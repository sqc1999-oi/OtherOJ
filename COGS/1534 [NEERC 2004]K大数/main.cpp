#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <fstream>
#include <cstdarg>
using namespace std;
const int N = 2e6;
struct seg_node
{
	seg_node *lc, *rc;
	int val;
} pool[N];
int cnt;
seg_node *new_node()
{
	assert(cnt < N);
	return &pool[cnt++];
}
seg_node *update(seg_node *n, int l, int r, int k)
{
	seg_node *x = new_node();
	memcpy(x, n, sizeof(seg_node));
	x->val++;
	if (l != r - 1)
		if (k < (l + r) / 2) x->lc = update(x->lc, l, (l + r) / 2, k);
		else x->rc = update(x->rc, (l + r) / 2, r, k);
	return x;
}
int query(seg_node *x, seg_node *y, int l, int r, int k)
{
	if (l == r - 1) return l;
	if (k <= y->lc->val - x->lc->val) return query(x->lc, y->lc, l, (l + r) / 2, k);
	return query(x->rc, y->rc, (l + r) / 2, r, k - (y->lc->val - x->lc->val));
}
void delete_n(int n, ...)
{
	va_list li;
	va_start(li, n);
	while (n--) delete[] va_arg(li, void *);
	va_end(li);
}
int main()
{
	ifstream cin("kthnumber.in");
	ofstream cout("kthnumber.out");
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	seg_node **rt = new seg_node *[n + 1];
	rt[0] = new_node();
	rt[0]->lc = rt[0]->rc = rt[0];
	rt[0]->val = 0;
	int *a = new int[n], *b = new int[n];
	for (int i = 0; i < n; i++) cin >> a[i];
	memcpy(b, a, sizeof(int)*n);
	sort(b, b + n);
	int *e = unique(b, b + n);
	for (int i = 0; i < n; i++)
		rt[i + 1] = update(rt[i], 0, e - b, lower_bound(b, e, a[i]) - b);
	for (int i = 0; i < m; i++)
	{
		int l, r, k;
		cin >> l >> r >> k;
		cout << b[query(rt[l - 1], rt[r], 0, e - b, k)] << endl;
	}
	delete_n(3, rt, a, b);
}
