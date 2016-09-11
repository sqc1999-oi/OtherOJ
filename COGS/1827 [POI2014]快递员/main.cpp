#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <fstream>
using namespace std;
const int N = 1e7;
struct seg_node
{
	seg_node *l, *r;
	int val;
} pool[N];
seg_node *new_node()
{
	static int cnt = 0;
	assert(cnt < N);
	return &pool[cnt++];
}
seg_node *update(seg_node *n, int l, int r, int k)
{
	seg_node *x = new_node();
	memcpy(x, n, sizeof(seg_node));
	x->val++;
	if (l != r - 1)
		if (k < (l + r) / 2) x->l = update(x->l, l, (l + r) / 2, k);
		else x->r = update(x->r, (l + r) / 2, r, k);
	return x;
}
int query(seg_node *x, seg_node *y, int l, int r, int k)
{
	if (l == r - 1) return y->val - x->val > k ? l : -1;
	if (y->l->val - x->l->val > k) return query(x->l, y->l, l, (l + r) / 2, k);
	if (y->r->val - x->r->val > k) return query(x->r, y->r, (l + r) / 2, r, k);
	return -1;
}
int main()
{
	ifstream cin("kur.in");
	ofstream cout("kur.out");
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	seg_node **rt = new seg_node *[n + 1];
	rt[0] = new_node();
	rt[0]->l = rt[0]->r = rt[0];
	rt[0]->val = 0;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		rt[i + 1] = update(rt[i], 0, n, x - 1);
	}
	for (int i = 0; i < m; i++)
	{
		int l, r;
		cin >> l >> r;
		cout << query(rt[l - 1], rt[r], 0, n, (r - l + 1) / 2) + 1 << endl;
	}
	delete[] rt;
}
