#include <cstdio>

int n, ans, a[1005];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    for(int i = 1; i < n-1; i++)
        ans += (a[i]>a[i-1]&&a[i+1]<a[i])||
               (a[i]<a[i-1]&&a[i+1]>a[i]);
    printf("%d\n", ans);
    return 0;
}