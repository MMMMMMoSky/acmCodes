#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define INF (1<<25)
using namespace std;

int n, m, beg[1005], maxbuy[105], firbuy[1005];
vector <int> pighou[1005];

struct Edge {int u, v, flow, cap;};

struct Dinic
{
	int s, t, e, d[111], cur[111];
	vector <int> G[111];
	Edge E[22222];

	void addedge (int u, int v, int cap)
	{
		G[u].push_back(e), G[v].push_back(e+1);
		E[e].u = u, E[e].v = v, E[e++].cap = cap;
		E[e].u = v, E[e].v = u, E[e++].cap = 0;
	}

	bool BFS ()
	{
		memset (d, -1, sizeof d);
		queue <int> q;
		q.push(s); d[s] = 0;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (int i = G[u].size()-1; i >= 0; i--)
			{
				Edge e0 = E[G[u][i]];
				if (d[e0.v] < 0 && e0.flow < e0.cap)
					d[e0.v] = d[u]+1, q.push(e0.v);
			}
		}
		return d[t] >= 0;
	}

	int DFS (int u, int flow)
	{
		if (u == t || !flow) return flow;

		int f1 = 0, f2;
		for (int &i = cur[u]; i >= 0; i--)
		{
			Edge &e1 = E[G[u][i]];
			Edge &e2 = E[G[u][i]^1];
			if (d[e1.v] != d[u] + 1) continue;
			f2 = DFS(e1.v,min(flow,e1.cap-e1.flow));
			if (f2 > 0) 
				f1 += f2, e1.flow += f2,
				flow -= f2, e2.flow -= f2;
			if (!flow) break;
		}
		return f1;
	}

	void work ()
	{
		int mxf = 0;
		while (BFS())
		{
			for (int i = s; i <= t; i++) cur[i] = G[i].size()-1;
			mxf += DFS(s,1<<30);
		}
		printf ("%d\n", mxf);
	}
}Solve;

void ReadinData ()
{
	scanf ("%d %d", &m, &n);
	for (int i = 1; i <= m; i++) scanf ("%d", beg+i);
	for (int i = 1; i <= n; i++)
	{
		int num, tmp; scanf ("%d", &num);
		for (int j = 1; j <= num; j++)
		{
			scanf ("%d", &tmp);
			pighou[tmp].push_back(i);
			if (!firbuy[tmp]) firbuy[tmp] = i;
		}
		scanf ("%d", maxbuy+i);
	}
}

void BuildGraph ()
{
	Solve.s = 0, Solve.t = n+1;
	for (int i = 1; i <= m; i++) Solve.addedge(Solve.s,firbuy[i],beg[i]);
	for (int i = 1; i <= n; i++) Solve.addedge(i,Solve.t,maxbuy[i]);
	for (int i = 1; i <= m; i++)
	for (int j = pighou[i].size()-1; j > 0; j--)
		Solve.addedge(pighou[i][j-1],pighou[i][j],INF);
}

int main ()
{
	ReadinData();
	BuildGraph();
	Solve.work();
	return 0;
}
