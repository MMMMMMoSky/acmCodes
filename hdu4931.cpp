#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
	int T;
	int a[10];
	scanf("%d", &T);
	while(T--)
	{
		for(int i = 1; i <= 6; i++)
			scanf("%d", a+i);
		sort(a+1, a+7);		
		int flag = a[6]+a[5]-a[2]-a[3]-a[4];
		if(flag > 0) 
			printf("Grandpa Shawn is the Winner!\n");
		else
			printf("What a sad story!\n");
	}
	return 0;
}
