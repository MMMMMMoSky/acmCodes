#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n, m, sum;

struct Edge {short u, v, flow, cap;};

struct NetWorkFlow 
{
	int s, t, e, d[2555], cur[2555];
	vector <int> G[2555];
	Edge E[3000005];

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
		d[s] = 0; q.push(s);
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (int i = G[u].size()-1; i >= 0; i--)
			{
				Edge e0 = E[G[u][i]];
				if (d[e0.v] < 0 && e0.cap>e0.flow)
					d[e0.v] = d[u] + 1, q.push(e0.v);
			}
		}
		return d[t] >= 0;
	}

	int DFS (int u, int flow)
	{
		if (u == t || !flow) return flow; // &&
		int f1 = 0, f2;
		for (int &i = cur[u]; i >= 0; i--)
		{
			Edge &e1 = E[G[u][i]];
			Edge &e2 = E[G[u][i]^1];
			if (d[u]+1 != d[e1.v]) continue;
			f2 = DFS(e1.v,min(flow,e1.cap-e1.flow));
			if (f2 > 0) f1 += f2, flow -= f2,
				    e1.flow += f2, e2.flow -= f2;
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
		printf ("%d\n", sum-mxf);
	}
}Solve;

int get ()
{
	int x = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
	return x;
}

void BuildGraph ()
{
	int num, whi, earn, used, hire;
	n = get(), m = get();
	Solve.s = 0, Solve.t = n+m+1;
	for (int i = 1; i <= n; i++)
	{
		earn = get(), num = get(), sum += earn;
		Solve.addedge(Solve.s,i,earn);
		for (int j = 1; j <= num; j++) 
		{
			used = get(), hire = get();
			Solve.addedge(i,used+n,hire);
		}
	}
	for (int i = 1; i <= m; i++) Solve.addedge(i+n,Solve.t,get());;
}

int main ()
{
	BuildGraph();
	Solve.work();
	return 0;
}
