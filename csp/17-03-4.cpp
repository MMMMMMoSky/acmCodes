#include <cstdio>
#include <algorithm>
using namespace std;

int i, n, m, f[100005];

struct edge {
	int u, v, len;
	bool operator < (edge t) const {
		return len < t.len;
	}
}E[200005];

int find(int x)
{
	return f[x] = f[x]==x?x:find(f[x]);
}

int main()
{
	scanf("%d%d", &n, &m);
	for(i = 0; i < m; i++)
		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].len);
	sort(E, E+m);
	for(i = 0; i <= n; i++)
		f[i] = i;
	for(i = 0; i < m && find(1)!=find(n); i++)
	{
		int u = E[i].u, v = E[i].v;
		int fu = find(u), fv = find(v);
		f[fu] = fv;
	}
	printf("%d\n", E[i-1].len);
	return 0;
}
