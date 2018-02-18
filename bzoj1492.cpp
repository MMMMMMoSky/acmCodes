#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#define MX 100005
using namespace std;

int n;
double A[MX], B[MX], R[MX], f[MX], ans;
const double eps = 1e-9;

struct SplayTree
{
	int tot, root, fa[MX], lc[MX], rc[MX], sz[MX];
	double x[MX], y[MX];

	void rotate (int rt)
	{
		int tmp = fa[rt];
		if (fa[tmp])
		{
			if (lc[fa[tmp]]==tmp) lc[fa[tmp]] = rt;
			else rc[fa[tmp]] = rt;
		}
		else root = rt;
		if (lc[tmp] == rt)
			lc[tmp] = rc[rt], rc[rt] = tmp;
		else	rc[tmp] = lc[rt], lc[rt] = tmp;
		fa[rt] = fa[tmp], fa[tmp] = rt;
		fa[lc[tmp]] = fa[rc[tmp]] = tmp;
		fa[lc[rt]] = fa[rc[rt]] = rt;
		sz[tmp] = sz[lc[tmp]] + sz[rc[tmp]] + 1;
		sz[rt] = sz[lc[rt]] + sz[rc[rt]] + 1;
	}

	int rank (int rt, int k)
	{
		if (sz[lc[rt]] == k-1) return rt;
		if (sz[lc[rt]] > k-1) return rank(lc[rt],k);
		return rank(rc[rt],k-sz[lc[rt]]-1);
	}

	int find (int rt, double k)
	{
		if (x[rt] - k > eps) return lc[rt] ? find(lc[rt],k) : rt;
		if (k - x[rt] > eps) return rc[rt] ? find(rc[rt],k) : rt;
		return rt;
	}

	int pre (int rt)
	{
		splay(rt);
		rt = lc[rt];
		while (rt && rc[rt]) rt = rc[rt];
		return rt;
	}

	int suf (int rt)
	{
		splay(rt);
		rt = rc[rt];
		while (rt && lc[rt]) rt = lc[rt];
		return rt;
	}

	void splay (int rt)
	{
		while (rt != root)
		{
			if (fa[fa[rt]] && (lc[fa[rt]]==rt) ==
				(lc[fa[fa[rt]]]==fa[rt]))
				rotate(fa[rt]);
			rotate(rt);
		}
	}

	void merge (int l, int r)
	{
		if (!l) {root = r; return;}
		if (!r) {root = l; return;}
		root = l;
		int rt = root;
		while (rc[rt]) rt = rc[rt];
		splay(rt);
		rc[rt] = r, fa[r] = rt, sz[rt] += sz[r];
	}

	void insert (int i)
	{
		int rt = root;
		while (1)
		{
			sz[rt]++;
			if (x[rt]-x[i] > eps)
			{
				if (lc[rt]) rt = lc[rt];
				else {lc[rt] = i; break;}
			}
			else 
			{
				if (rc[rt]) rt = rc[rt];
				else {rc[rt] = i;break;}
			}
		}
		sz[i] = 1; fa[i] = rt; splay(i); tot++; 
	}

	void del (int rt)
	{
		splay(rt);
		int l = lc[rt], r = rc[rt];
		fa[l] = fa[r] = 0;
		merge(l, r);
		tot--;
	}

	bool under (int p, int p1, int p2)
	{
		double cj = (x[p]-x[p1])*(y[p2]-y[p1]);
		cj -= (x[p2]-x[p1])*(y[p]-y[p1]);
		return cj >= -eps;
	}

	void update (int i)
	{
		y[i] = f[i]/(A[i]*R[i]+B[i]), x[i] = y[i]*R[i];
		if (!tot) {root = i; ++tot; return;}
		int l, r = find(root, x[i]);
		if (x[r] - x[i] < -eps) l = r, r = suf(r);
		else l = pre(r);
		if (l&&r&&under(i,l,r)) return;
		if (r)
		{
			int nxtr = suf(r);
			while(nxtr&&under(r,i,nxtr))
				del(r), r = nxtr, nxtr = suf(nxtr);
		}
		if (l)
		{
			int lasl = pre(l);
			while(lasl&&under(l,lasl,i))
				del(l), l = lasl, lasl = pre(lasl);
		}
		insert(i);
	}

	double calc (int rt, int i)
	{
		return A[i]*x[rt]+B[i]*y[rt];
	}

	double query (int i)
	{
		int l = 1, r = tot, mid, nxt; double cmid, cnxt;
		if (r == 1) return calc(rank(root,l),i);
		while (l < r)
		{
			if (l+1==r) mid = rank(root,l);
			else mid = rank(root,(l+r)/2);
			nxt = suf(mid);
			cmid = calc(mid,i), cnxt = calc(nxt,i);
			if (cmid-cnxt <= eps && cmid-cnxt >= -eps) 
			return cmid;
			if (cnxt-cmid > eps) l = (l+r)/2+1;
			else r = (l+r)/2;
		}
		return max(cmid, cnxt);
	}
}Tree;

double getfloat ()
{
	double res = 0.0; char c = getchar(); bool flag = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0')
	{
		res = res*10.0+1.0*(c-48), c = getchar();
		if (c == '.') {flag = 1; break;}
	}
	if (flag)
	{
		c = getchar(); double x = 0.1;
		while (c <= '9' && c >= '0') 
			res += x*(c-48), x /= 10.0, c = getchar();
	}
	return res;
}

void ReadinData ()
{
	freopen ("cash.in", "r", stdin);
	freopen ("cash.out", "w", stdout);
	scanf ("%d", &n);
	f[1] = ans = getfloat();
	for (int i = 1; i <= n; i++)
		A[i] = getfloat(), B[i] = getfloat(), R[i] = getfloat();
	Tree.update(1);
}

void Solve ()
{
	for (int i = 2; i <= n; i++)
	{
		f[i] = max(ans, Tree.query(i));
		ans = max(ans, f[i]);
		Tree.update(i);
	}
	printf ("%.3lf\n", ans);
}

int main ()
{
	ReadinData();	
	Solve();
	return 0;
}
