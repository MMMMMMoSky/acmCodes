#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int T, n, k[10005];
char s[20005], t[10005];

struct SAM
{
	#define MX 50005
	int tot, last, root, l[MX], f[MX], go[MX][30], flag[MX];
	void initialize ()
	{
		tot = last = root = 1;
		memset (f, 0, sizeof f);
		memset (l, 0, sizeof l);
		memset (go, 0, sizeof go);
		memset (flag, 0x3f, sizeof flag);
	}
	void add (char c)
	{
		int x = c-'a'+1;
		int p = last, np = ++tot; last = np;
		l[np] = l[p] + 1;
		for(;p&&!go[p][x];p=f[p]) 
			go[p][x] = np, flag[p] = min(flag[p],x);
		if (!p) f[np] = root;
		else
		{
			int q = go[p][x];
			if (l[q] == l[p]+1) f[np] = q;
			else
			{
				int nq = ++tot; l[nq] = l[p] + 1;
				memcpy(go[nq], go[q], sizeof go[q]);
				f[nq] = f[q];
				f[np] = f[q] = nq;
				flag[nq] = flag[q];
				for(;go[p][x]==q;p=f[p]) 
					go[p][x] = nq, flag[p] = min(flag[p],x);
			}
		}
	}
	
	void get_t ()
	{
		int p = root;
		for (int i = 1; i <= n; i++)
		{
			t[i] = flag[p]+'a'-1;
			p = go[p][flag[p]];
		}
	}
}Solve;

int KMP ()
{
	printf ("%s\n%s\n", s+1,t+1);
	int m = n; n *= 2;
	k[1] = k[2] = 1;
	for (int i = 2, j = 1; i <= m; j=k[++i])
	{
		while (j > 1 && t[j] != t[i]) j = k[j];
		k[i+1] = (t[j]==t[i])*j+1;
	}
	for (int i = 1, j = 1; i <= n; i++)
	{
		while (j > 1 && s[i] != t[j]) j = k[j];
		if (s[i] == t[j]) j++;
		if (j > m) return i-m-n+1>0?i-m-n+1:i-m+1;
	}
}

int main ()
{
	scanf ("%d", &T);
	while (T--)
	{
		memset (s, 0, sizeof s);
		memset (t, 0, sizeof t);
		scanf ("%s", s+1);
		n = strlen(s+1);
		Solve.initialize();
		for (int i = 1; i <= n; i++) s[i+n] = s[i];
		for (int i = 1; i <= n*2; i++) Solve.add(s[i]);
		Solve.get_t();
		printf ("%d\n", KMP());
	}
}
