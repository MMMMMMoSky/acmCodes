#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int T, n, m, sum, v[33];
long long ans, f[1005];

int getint ()
{
	int x = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
	return x;
}

int main ()
{
	T = getint();
	for (int num = 1; num <= T; num++)
	{
		sum = ans = 0;
		memset (f, 0, sizeof f);
		f[0] = 1;

		n = getint(), m = getint();
		for (int i = 1; i <= n; i++) sum += (v[i] = getint());
		sort(v+1, v+n+1);
		if (v[1] > m) {printf ("%d 0\n", num); continue;}

		for (int i = n; i; i--)
		{
			sum -= v[i];
			for (int j = 0; j < v[i] && m-sum-j >= 0; j++)
				ans += f[m-sum-j];
			for (int j = m; j >= v[i]; j--) f[j] += f[j-v[i]];
		}

		printf ("%d %lld\n", num, ans);
	}
	return 0;
}
/*
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int T, n, m, sum, v[33];
long long ans, f[1005];

int main ()
{
	scanf ("%d", &T);
	for (int num = 1; num <= T; num++)
	{
		sum = ans = 0;

		scanf ("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) scanf ("%d", v+i);
		sort(v+1, v+n+1);
		if (v[1] > m) {printf ("%d 0\n", num); continue;}

		for (int i = 1; i < n; i++)
		{
			if (sum > m) break;
			memset (f, 0, sizeof f);
			f[sum] = 1;
			for (int ii = i+1; ii <= n; ii++)
			{
				for (int j = m; j >= v[ii]+sum; j--)
					f[j] = f[j] + f[j-v[ii]];
			}
			int tmp = max(m-v[i]+1,sum);
			for (int j = tmp; j <= m; j++) ans += f[j];
			sum += v[i];
		}

		printf ("%d %lld\n", num, ans);
	}
	return 0;
}
*/
