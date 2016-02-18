#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdarg>
#include <cctype>
using namespace std;
const int N = 1e4;
struct splay_node
{
	static splay_node *nul;
	struct constructor
	{
		constructor()
		{
			nul = new splay_node;
			nul->l = nul->r = nul->p = nul;
		}
	};
	static constructor ctor;
	splay_node *l, *r, *p;
	int v, m;
	splay_node() :l(nul), r(nul), p(nul), v(), m() {}
	bool is_root() { return p == nul || p->l != this&&p->r != this; }
	void maintain() { m = max(v, max(l->m, r->m)); }
	void transplant(splay_node *x)
	{
		x->p = p;
		if (p->l == this) p->l = x;
		else if (p->r == this) p->r = x;
	}
	void left_rotate()
	{
		splay_node *x = r;
		r = x->l;
		r->p = this;
		transplant(x);
		x->l = this;
		p = x;
		maintain();
		x->maintain();
	}
	void right_rotate()
	{
		splay_node *x = l;
		l = x->r;
		l->p = this;
		transplant(x);
		x->r = this;
		p = x;
		maintain();
		x->maintain();
	}
	void splay()
	{
		while (!is_root())
		{
			if (p->is_root())
				if (p->l == this) p->right_rotate();
				else p->left_rotate();
			else
			{
				splay_node *x = p->p;
				if (p->l == this)
					if (x->l == p) x->right_rotate(), p->right_rotate();
					else p->right_rotate(), x->left_rotate();
				else
					if (x->r == p) x->left_rotate(), p->left_rotate();
					else p->left_rotate(), x->right_rotate();
			}
		}
	}
};
splay_node *splay_node::nul;
splay_node::constructor splay_node::ctor;
void access(splay_node *n)
{
	splay_node *x = n, *y = splay_node::nul;
	while (x != splay_node::nul)
	{
		x->splay();
		x->r = y;
		x->maintain();
		y = x;
		x = x->p;
	}
	n->splay();
}
int solve(splay_node *n)
{
	splay_node *x = n, *y = splay_node::nul;
	int ret = 0;
	while (x != splay_node::nul)
	{
		x->splay();
		if (x->p == splay_node::nul) ret = max(x->r->m, y->m);
		x->r = y;
		x->maintain();
		y = x;
		x = x->p;
	}
	n->splay();
	return ret;
}
splay_node a[N];
struct edge
{
	int to, pow, id;
	edge(int to, int pow, int id) :to(to), pow(pow), id(id) {}
};
vector<edge> e;
vector<int> g[N];
splay_node *belong[N - 1];
void add_edge(int u, int v, int w, int id)
{
	g[u].push_back(e.size());
	e.push_back(edge(v, w, id));
}
void dfs(int u, int p)
{
	for (int i = 0; i < g[u].size(); i++)
	{
		edge &x = e[g[u][i]];
		if (x.to != p)
		{
			a[x.to].v = a[x.to].m = x.pow;
			a[x.to].p = a + u;
			belong[x.id] = a + x.to;
			dfs(x.to, u);
		}
	}
}
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
			(x *= 10) += ch - '0';
			ch = getchar();
		} while (isdigit(ch));
	}
	va_end(li);
}
int next_ch()
{
	int ch;
	do ch = getchar();
	while (!isupper(ch));
	return ch;
}
int main()
{
	int T;
	read(1, &T);
	while (T--)
	{
		int n;
		read(1, &n);
		e.clear();
		for (int i = 0; i < n; i++)
		{
			a[i] = splay_node();
			g[i].clear();
		}
		for (int i = 0; i < n - 1; i++)
		{
			int a, b, c;
			read(3, &a, &b, &c);
			a--, b--;
			add_edge(a, b, c, i);
			add_edge(b, a, c, i);
		}
		dfs(0, -1);
		while (true)
		{
			int ch = next_ch(), x, y;
			if (ch == 'D') break;
			read(2, &x, &y);
			if (ch == 'Q')
			{
				access(a + x - 1);
				printf("%d\n", solve(a + y - 1));
			}
			else if (ch == 'C')
			{
				belong[x - 1]->splay();
				belong[x - 1]->v = y;
				belong[x - 1]->maintain();
			}
		}
	}
}