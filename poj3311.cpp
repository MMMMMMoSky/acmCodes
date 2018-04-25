#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, d[15][15], f[15][1<<12];

int F(int x, int s)
{
    if(f[x][s] > 0) return f[x][s];
    f[x][s] = 1<<25;
    for(int i = 1; i <= n; i++)
    if(s&(1<<(i-1))) {
        f[x][s] = min(f[x][s], F(i, s-(1<<(i-1)))+d[x][i]);
    }
    return f[x][s];
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        memset(f, -1, sizeof f);
        memset(d, (1<<6)-1, sizeof d);
        for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++)
            scanf("%d", d[i]+j);
        
        for(int k = 0; k <= n; k++)
        for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++)
            d[i][j] = min(d[i][j], d[i][k]+d[k][j]);

        for(int i = 0; i <= n; i++)
            f[i][0] = d[i][0];

        printf("%d\n", F(0, (1<<n)-1));
    }
    return 0;
}
