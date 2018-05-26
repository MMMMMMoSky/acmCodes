#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int n, m, sumcow, A[205], B[205];
long long sumtime, D[205][205];

struct Edge {int u, v, flow, cap;};

struct Dinic
{
	int s, t, e, cur[505], d[505];
	vector <int> G[505];
	Edge E[100005]; // E[40005]

	void addedge (int u, int v, int cap)
	{
		G[u].push_back(e), G[v].push_back(e+1);
		E[e].u = u, E[e].v = v, E[e++].cap = cap;
		E[e].u = v, E[e].v = u, E[e++].cap = 0;
	}

	bool BFS ()
	{
		queue <int> q;
		while (!q.empty()) q.pop();
		memset (d, -1, sizeof d);
		q.push(0); d[0] = 0;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (int i = G[u].size()-1; i >= 0; i--)
			{
				Edge e0 = E[G[u][i]];
				if (d[e0.v] < 0 && e0.cap > e0.flow) 
					d[e0.v] = d[u]+1, q.push(e0.v);
			}
		}
		return d[t] > 0;
	}

	int DFS (int u, int flow)
	{
		if (u == t || !flow) return flow;
		int f1 = 0, f2;
		for (int &i = cur[u]; i >= 0; i--)
		{
			Edge &e1 = E[G[u][i]];
			Edge &e2 = E[G[u][i]^1];
			if (d[u]+1==d[e1.v] && (f2=DFS(e1.v,min(flow,e1.cap-e1.flow))) > 0)
			{
				f1 += f2, flow -= f2;
				e1.flow += f2, e2.flow -= f2;
				if (!flow) break;
			}
		}
		return f1;
	}

	int maxflow ()
	{
		int res = 0;
		while (BFS())
		{
			for (int i = s; i <= t; i++) cur[i] = G[i].size()-1;
			res += DFS(s,1<<30);
		}
		return res;
	}
	
	void replace (long long T) // long long
	{
		e = n*4;
		for (int i = s; i <= t; i++)
		{
			int siz = G[i].size();
			while (siz && G[i][siz-1] >= e) G[i].resize(--siz);
									//siz
		}
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		if (D[i][j] <= T) addedge(i, j+n, 1<<30);
		for (int i = 0; i < e; i++) E[i].flow = 0; // whole
	}
}Solve;

void ReadinData ()
{
	scanf ("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d %d", A+i, B+i);
	memset(D, 0x3f, sizeof D);
	for (int i = 1; i <= n; i++) D[i][i] = 0, sumcow += A[i];
	for (int i = 1; i <= m; i++) 
	{
		int a, b; long long c; 
		scanf ("%d %d %lld", &a, &b, &c);
		D[a][b] = D[b][a] = min(D[a][b],c);
		sumtime += c;
	}
}

void Initialize ()
{
	for (int k = 1; k <= n; k++)
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++) // j = i
	if (i!=j) D[i][j] = min(D[i][j], D[i][k]+D[k][j]);
	Solve.s = 0, Solve.t = n*2+1;
	for (int i = 1; i <= n; i++)
		Solve.addedge(0,i,A[i]), Solve.addedge(i+n,n*2+1,B[i]);
}

void Soluation ()
{
	long long l = 0, r = sumtime+1, mid;
	while (l < r)
	{
		mid = l+r>>(long long)1;
		Solve.replace(mid);
		int res = Solve.maxflow();
		if (res == sumcow) r = mid;
		else l = mid + 1;
	}
	if (l <= sumtime) printf ("%lld\n", l);
	else puts("-1");
}

int main ()
{
	ReadinData();
	Initialize();
	Soluation();
	return 0;
}
