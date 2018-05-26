#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int tot, a[10005], hash[1000005], vis[1000005];

int get ()
{
	char c = getchar(); int x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
	return x;
}

int main ()
{
	int n, m;
	n = get(), m = get();
	for (int i = 1; i <= n; i++)
	{
		int tmp = get();
		if (!hash[tmp]) hash[tmp] = ++tot;
		a[i] = hash[tmp];
	
	for (int i = 1; i <= m; i++)
	{
		char cmd[3]; scanf ("%s", cmd);
		int l = get(), r = get(), ans = 0;
		if (cmd[0] == 'R') 
		{
			if (!hash[r]) hash[r] = ++tot;
			a[l] = hash[r];
		}
		else
		{
			for (int j = l; j <= r; j++)
			ans += vis[a[j]]!=i, vis[a[j]] = i;
			printf ("%d\n", ans);
		}
	}
	return 0;
}
