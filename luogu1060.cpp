#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, v[30], w[30], f[30005];

int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", w+i, v+i);
		v[i] *= w[i];
	}
	for(int i = w[1]; i <= m; i++)
		f[i] = v[1];
	for(int i = 2; i <= n; i++)
	for(int j = m; j >= w[i]; j--)
		f[j] = max(f[j], f[j-w[i]]+v[i]);
	printf("%d\n", f[m]);
	return 0;
}
