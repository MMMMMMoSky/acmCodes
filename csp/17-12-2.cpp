#include <cstdio>

int n, k;
int nx[1005], lst[1005];

int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++)
		nx[i] = (i+1)%n, lst[i] = (i+n-1)%n;
	int num = 1, pos = 0;
	for(int i = 1; i < n; i++)
	{
		while(num%10 != k && num%k) 
			num++, pos = nx[pos];
		nx[lst[pos]] = nx[pos];
		lst[nx[pos]] = lst[pos];
		num++, pos = nx[pos];
	}
	printf("%d\n", pos+1);
	return 0;
}
