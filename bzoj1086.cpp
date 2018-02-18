#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int get ()
{
	char c = getchar(); int x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
	return x;
}

void put (int x, char c)
{
	if (!x) putchar ('0');
	char s[15]; int num = 0;
	while (x) s[num++] = (x%10)+48, x /= 10;
	while (num) putchar (s[--num]);
	putchar (c);
}

int n, sz, top, tot, s[2005], bel[2005], root[1005];
vector <int> G[1005];

void addedge (int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

void dfs (int x, int fa)
{
	int tmp = top;
	for (int i = 0; i < G[x].size(); i++)
	if (G[x][i] != fa)
	{
		dfs (G[x][i], x);
		if (top-tmp >= sz) 
		{
			root[++tot] = x;
			while (top != tmp) bel[s[top--]] = tot;
		}
	}
	s[++top] = x;
}

int main ()
{
	n = get(), sz = get();
	for (int i = 1; i < n; i++) addedge(get(), get());	
	dfs(1, 0);
	while (top) bel[s[top--]] = tot;
	put (tot, '\n');
	for (int i = 1; i <= n; i++) put (bel[i], ' ');
	putchar ('\n');
	for (int i = 1; i <= tot; i++) put (root[i], ' ');
	return 0;
}
