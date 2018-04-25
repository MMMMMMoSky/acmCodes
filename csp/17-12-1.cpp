#include <cstdio>
#include <algorithm>
using namespace std;

int n, ans = 1<<25;
int s[1005];

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", s + i);
	sort(s, s+n);
	for(int i = 1; i < n; i++)
		ans = min(ans, s[i]-s[i-1]);
	printf("%d\n", ans);
	return 0;
}
