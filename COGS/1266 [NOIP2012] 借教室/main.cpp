#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
char buf[20000000];
inline int read()
{
	static int pos = 0;
	int x = 0;
	while (!isdigit(buf[pos])) pos++;
	do
	{
		(x *= 10) += buf[pos] - '0';
		pos++;
	} while (isdigit(buf[pos]));
	return x;
}
class SegmentTree
{
	struct node
	{
		int L, R, Min, Add;
		node *LC, *RC;
		node(int l, int r, int min, node *lc, node *rc) :L(l), R(r), Min(min), Add(0), LC(lc), RC(rc) {}
	};
	node *root;
	node *build(int l, int r)
	{
		if (l == r) return new node(l, r, read(), NULL, NULL);
		node *lc = build(l, (l + r) / 2);
		node *rc = build((l + r) / 2 + 1, r);
		return new node(l, r, min(lc->Min, rc->Min), lc, rc);
	}
	void pushDown(node *n)
	{
		n->LC->Add += n->Add;
		n->RC->Add += n->Add;
		n->LC->Min += n->Add;
		n->RC->Min += n->Add;
		n->Add = 0;
	}
	bool update(int l, int r, int val, node *n)
	{
		if (l == n->L&&r == n->R)
		{
			n->Add += val;
			n->Min += val;
			return n->Min >= 0;
		}
		pushDown(n);
		bool tmp;
		if (r <= n->LC->R) tmp = update(l, r, val, n->LC);
		else if (l >= n->RC->L) tmp = update(l, r, val, n->RC);
		else tmp = update(l, n->LC->R, val, n->LC) && update(n->RC->L, r, val, n->RC);
		n->Min = min(n->LC->Min, n->RC->Min);
		return tmp;
	}
public:
	SegmentTree(int n) { root = build(1, n); }
	bool Update(int l, int r, int val) { return update(l, r, val, root); }
};
int main()
{
	FILE *f = fopen("classrooms.in", "r");
	freopen("classrooms.out", "w", stdout);
	fread(buf, 1, 20000000, f);
	int n = read(), m = read();
	SegmentTree T(n);
	for (int i = 1; i <= m; i++)
	{
		int d = read(), s = read(), t = read();
		if (!T.Update(s, t, -d))
		{
			printf("-1\n%d\n", i);
			return 0;
		}
	}
	puts("0");
}
