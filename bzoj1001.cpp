#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int get ()
{
	char c = getchar(); int x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
	return x;
}

int n, m, MIN = 1<<30, hen[1005][1005], zon[1005][1005], xie[1005][1005];
int e, h[2000005], nx[6000005], to[6000005], w[6000005];
int s, t, d[2000005];
bool inq[2000005];
queue <int> q;

void addedge (int a, int b, int v)
{
	nx[++e] = h[a], h[a] = e, to[e] = b, w[e] = v;
	nx[++e] = h[b], h[b] = e, to[e] = a, w[e] = v;
}

void Initialize ()
{
	n = get(), m = get();
	for (int i = 1; i <= n; i++) 
	for (int j = 1; j <  m; j++) 
		MIN = min(MIN, hen[i][j] = get());
	for (int i = 1; i <  n; i++)
	for (int j = 1; j <= m; j++) 
		MIN = min(MIN, zon[i][j] = get());
	for (int i = 1; i <  n; i++)
	for (int j = 1; j <  m; j++) 
		MIN = min(MIN, xie[i][j] = get());
}

void Get_newG ()
{
	if (n == 1 || m == 1) return ;
	s = 0, t = (n-1)*(m-1)*2+1;
	for (int i = 1; i < m; i++)
	{
		addedge (s, i, hen[1][i]);
		addedge (t, t-m+i, hen[n][i]);
	}
	for (int i = 2; i < n; i++)
	for (int j = 1; j < m; j++)
	{
		int a = (i-2)*(m-1)*2+m-1+j;
		addedge (a, a+m-1, hen[i][j]);
	}
	for (int i = 1; i < n; i++)
	{
		addedge (t, (i-1)*(m-1)*2+m, zon[i][1]);
		addedge (s, (i-1)*(m-1)*2+m-1, zon[i][m]);
	}
	for (int i = 1; i < n; i++)
	for (int j = 2; j < m; j++)
	{
		int a = (i-1)*(m-1)*2+j-1;
		addedge (a, a+m, zon[i][j]);
	}
	for (int i = 1; i < n; i++)
	for (int j = 1; j < m; j++)
	{
		int a = (i-1)*(m-1)*2+j;
		addedge (a, a+m-1, xie[i][j]);
	}
}

void Spfa ()
{
	if (n == 1 || m == 1) {printf ("%d\n", MIN); return;}
	memset (d, 0x3f, sizeof d);
	d[s] = 0; q.push(s);
	while (!q.empty())
	{
		int x = q.front(); q.pop(); inq[x] = 0;
		for (int i = h[x]; i; i = nx[i])
		if (d[to[i]] > d[x]+w[i]){
			d[to[i]] = d[x] + w[i];
			if (!inq[to[i]]) q.push(to[i]);
			inq[to[i]] = 1;
		}
	}
	printf ("%d\n", d[t]);
}

int main ()
{
	Initialize();
	Get_newG();
	Spfa();
	return 0;
}
