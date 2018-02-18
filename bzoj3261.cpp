// 2^24 > 10^7

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int get ()
{
	char c = getchar(); int x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
	return x;
}
int getcmd ()
{
	char c = getchar();
	while (c != 'A' && c != 'Q') c = getchar();
	return c == 'A';
}

struct node 
{
	int tot; node *lc, *rc;
	node () {tot = 0, lc = rc = NULL;}
};

struct PersistableTrie
{
	int cnt; node *root[600006];

	PersistableTrie () {root[0]=NULL;}

	void insert (node *rt, node *nrt, int x, int t)
	{
		node *rtlc = rt==NULL ? NULL : rt->lc;
		node *rtrc = rt==NULL ? NULL : rt->rc;
		nrt->tot = 1+(rt==NULL?0:rt->tot);
		if (!t) return ;
		if (x&t) 
		{
			nrt->rc = rtrc;
			insert (rtlc, nrt->lc=new node, x, t>>1);
		}
		else
		{
			nrt->lc = rtlc; 
			insert (rtrc, nrt->rc=new node, x, t>>1);
		}
	}
	void insert (int x)
	{
		root[++cnt] = new node;
		insert (root[cnt-1], root[cnt], x, 1<<24);
	}

	int  query (node *rt, node *nrt, int x, int t)
	{
		if (!t) return 0;
		if (nrt == NULL) return x;
		node *rtlc = rt==NULL ? NULL : rt->lc;
		node *rtrc = rt==NULL ? NULL : rt->rc;
		int ltot  =  rtlc==NULL ? 0 :  rtlc->tot;
		int rtot  =  rtrc==NULL ? 0 :  rtrc->tot;
		int nltot = nrt->lc==NULL ? 0 : nrt->lc->tot;
		int nrtot = nrt->rc==NULL ? 0 : nrt->rc->tot;
		if (x&t)
		{
			if (nrtot-rtot) 
				return t+query(rtrc,nrt->rc,x,t>>1);
			return query(rtlc,nrt->lc,x,t>>1);
		}
		else
		{
			if (nltot-ltot)
				return t+query(rtlc,nrt->lc,x,t>>1);
			return query(rtrc,nrt->rc,x,t>>1);
		}
	}
	void query (int l, int r, int x)
	{
		if (l==1) l = 2;
		int res = query (root[l-2], root[r-1], x, 1<<24);
		char s[15]; int len = 0;
		if (!res) putchar ('0');
		while (res) s[len++] = (res%10)+48, res /= 10;
		while (len) putchar (s[--len]);
		putchar ('\n');
	}
}Solve;

int n, m, sumxor;

int main ()
{
	n = get(), m = get();		
	for (int i = 1; i <= n; i++) Solve.insert(sumxor=sumxor^get());
	for (int i = 1; i <= m; i++)
	{
		int cmd = getcmd();
		if (cmd) Solve.insert(sumxor=sumxor^get());
		else
		{
			int l = get(), r = get(), x = get();
			Solve.query(l, r, x^sumxor);
		}
	}
	return 0;
}
