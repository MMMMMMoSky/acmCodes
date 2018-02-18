#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct node
{
	int b, w, f[808];
	void init (int n)
	{
		b = w = 0;
		for (int i = 0; i <= n; i++)
		f[i] = i;
	}
	int find (int x)
	{
		if (f[x] == x) return x;
		return f[x] = find(f[x]);
	}
	void merge (int a, int b)
	{
		f[find(a)] = find(b);
	}
};

int n, m;
bool map[205][205];

struct SegmentTree
{
	node T[808];
	#define LChild p<<1,l,mid
	#define RChild p<<1|1,mid+1,r

	void maintain (int p, int l, int r)
	{
		int lc = p<<1, rc = lc|1, mid = (l+r)/2;
		T[p].init(n<<2);
		T[p].b = T[lc].b + T[rc].b;
		T[p].w = T[lc].w + T[rc].w;
		for (int i = 1; i <= n; i++)
		T[p].f[i] = T[lc].f[i],
		T[p].f[i+n] = T[lc].f[i+n],
		T[p].f[i+n+n] = T[rc].f[i]+n*2,
		T[p].f[i+n+n+n] = T[rc].f[i+n]+n*2;
		for (int i = 1; i <= n; i++)
		if (map[mid][i]==map[mid+1][i])
		{
			int f1 = T[p].find(i+n);
			int f2 = T[p].find(i+n+n);
			if (f1 != f2)
			{
				T[p].w -= (map[mid][i]==0), 
				T[p].b -= (map[mid][i]==1);
				T[p].merge(f1,f2);
			}
		}
		for (int i = 1; i <= n; i++)
		{
			int fi = T[p].find(i);
			if (fi > n) T[p].f[fi] = T[p].f[i] = i;
		}
		for (int i = n*3+1; i <= n*4; i++)
		{
			int fi = T[p].find(i);
			if (fi <= n) T[p].f[i-n*2] = T[p].f[i];
			else T[p].f[fi] = T[p].f[i-n*2] = i-n*2;
		}
	}

	void make (int r, int p)
	{
		T[p].init(n<<2);
		for (int i = 1; i <= n; i++)
		T[p].merge(i,i+n);
		for (int i = 2; i <= n; i++)
		if (map[r][i]==map[r][i-1]) 
		{
			T[p].merge(i,i-1);
			T[p].merge(i+n,i+n-1);
		}
		for (int i = 1; i <= n; i++)
		if (T[p].f[i] == i) 
		T[p].w += map[r][i]==0, T[p].b += map[r][i]==1;
		for (int i = 1; i <= n; i++)
		if (T[p].f[i+n] == i+n) 
		T[p].w += map[r][i]==0, T[p].b += map[r][i]==1;
	}
	
	void build (int p, int l, int r)
	{
		if (l == r) make(r,p);
		else
		{
			int mid = (l+r)/2;
			build(LChild);
			build(RChild);
			maintain(p,l,r);
		}
	}

	void change (int p, int l, int r, int pos)
	{
		if (l == r) {make(r,p);return;}
		int mid = (l+r)/2;
		if (pos <= mid) change(LChild,pos);
		else change(RChild,pos);
		maintain(p,l,r);
	}

	void change (int x, int y)
	{
		map[x][y] = !map[x][y];
		change (1, 1, n, x);
	}

	void query ()
	{
		printf ("%d %d\n", T[1].b, T[1].w);
	}

}Solve;

int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
	scanf ("%d", map[i]+j);

	Solve.build(1,1,n);
	scanf ("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int x, y; scanf ("%d %d", &x, &y);
		Solve.change(x,y);
		Solve.query();
	}
	return 0;
}
