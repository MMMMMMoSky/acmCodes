#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int n, r, tot, ans, q[2005];
const double pi = 3.1415926, eps = 1e-7;

struct point
{
	double l, r;
	bool operator < (point k)
	const { return l < k.l; }
}P[2005];

void Initialize ()
{
	scanf ("%d %d", &n, &r);
	for (int i = 1; i <= n; i++)
	{
		int x, y; scanf ("%d %d", &x, &y);
		double theta = atan2(1.0*y,1.0*x);
		double alpha = acos(1.0*r/sqrt(1.0*x*x+1.0*y*y));
		P[i].l = theta - alpha, P[i].r = theta + alpha;
		if (P[i].r >= pi) P[i].r -= pi*2.0, P[i].l -= pi*2.0;
		if (P[i].l <= -pi) P[i].l += pi*2.0, swap(P[i].l,P[i].r);
	}
	sort(P+1, P+n+1);
}

int LIS (int beg)
{
	q[tot=1] = beg;
	for (int i = beg+1; i <= n && P[i].l <= P[beg].r; i++)
	{
		int l = 1, r = tot+1, mid;
		while (l < r)
		{
			mid = l+r>>1;
			if (P[q[mid]].r >= P[i].r) r = mid;
			else l = mid + 1;
		}
		if (q[l] == beg) continue;
		tot = max(tot,l), q[l] = i;
	}
	return tot;
}

void Soluation ()
{
	ans = 0;
	for (int i = 1; i <= n; i++) 
		ans = max(ans, LIS(i));
	printf ("%d\n", ans);
}

int main ()
{
	Initialize();
	Soluation();
	return 0;
}
