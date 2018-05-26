#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int K, C, M, maxd, D[250][250];

struct Edge {int u, v, flow, cap;};

struct Dinic
{
	int s, t, e, d[250], cur[250];
	vector <int> G[250];
	Edge E[80008];

	void addedge (int u, int v, int cap)
	{
		G[u].push_back(e), G[v].push_back(e+1);
		E[e].u = u, E[e].v = v, E[e++].cap = cap;
		E[e].u = v, E[e].v = u, E[e++].cap = 0;
	}

	void initialize ()
	{
		s = 0, t = K+C+1;
		for (int i = 1; i <= K; i++) addedge(i,t,M);
		for (int i = 1; i <= C; i++) addedge(s,i+K,1);
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

	void replace (int T)
	{
		e = K+C<<1; // <1> e=K+C;
		for (int i = s; i <= t; i++) // <2> i <= T
		{
			int siz = G[i].size();
			while (siz && G[i][siz-1] >= e) G[i].resize(--siz);
		}
		for (int i = 1; i <= C; i++)
		for (int j = 1; j <= K; j++)
		if (D[i+K][j] <= T) addedge(i+K,j,1111);
		for (int i = 0; i < e; i++) E[i].flow = 0;
	}
}Solve;

void ReadinData ()
{
	scanf ("%d %d %d", &K, &C, &M);
	for (int i = 1; i <= K+C; i++)
	for (int j = 1; j <= K+C; j++)
	scanf ("%d", D[i]+j);
}

void Initialize ()
{
	for (int i = 1; i <= K+C; i++)
	for (int j = 1; j <= K+C; j++)
	if (i != j && !D[i][j]) D[i][j] = 1<<29; // <3> 1<<30
	for (int k = 1; k <= K+C; k++)
	for (int i = 1; i <= K+C; i++)
	for (int j = 1; j <= K+C; j++)
	if (i != j) D[i][j] = min (D[i][j], D[i][k]+D[k][j]);
	for (int i = 1; i <= K+C; i++)
	for (int j = 1; j <= K+C; j++) 
	if (D[i][j] != (1<<29)) maxd = max(maxd, D[i][j]);

	Solve.initialize();
}

void Soluation ()
{
	int l = 0, r = maxd, mid;
	while (l < r)
	{
		mid = l+r>>1;
		Solve.replace(mid);
		int mxf = Solve.maxflow();
		if (mxf == C) r = mid;
		else l = mid + 1;
	}
	printf ("%d\n", l);
}

int main ()
{
	ReadinData();
	Initialize();
	Soluation();
	return 0;
}
