#include <cstdio>
#include <cstring>
#include <algorithm>
#define MX 100005
using namespace std;

int n, m, h, t, A[1005], C[1005];
bool f[MX], q[MX];

int main ()
{
	while (~scanf ("%d %d", &n, &m) && n+m)
	{
		for (int i = 1; i <= n; i++) scanf ("%d", A+i);
		for (int i = 1; i <= n; i++) scanf ("%d", C+i);
		memset (f, 0, sizeof f);
		int ans = 0; f[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			if (C[i] == 1)
			{
				for (int j = m; j >= A[i]; j--)
				if (!f[j] && f[j-A[i]]) f[j] = 1, ans++;
			}
			else if (A[i] * C[i] > m)
			{
				for (int j = A[i]; j <= m; j++)
				if (!f[j] && f[j-A[i]]) f[j] = 1, ans++;
			}
			else
			{
				for (int mod = 0; mod < A[i]; mod++)
				{	
				 	int sum = 0; h = t = q[0] = 0;
					for (int j = mod; j <= m; j+=A[i])
					{
						if (t-h == C[i]+1) sum -= q[++h];
						sum += (q[++t] = f[j]);
						if (!f[j] && sum) f[j] = 1, ans++;
					}
				}
			}
		}
		printf ("%d\n", ans);
	}
	return 0;
}
