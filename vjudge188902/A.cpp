#include <cstdio>
#include <cstring>
#include <cmath>

int n, a, last;
bool vis[3005];

int main()
{
    while(~scanf("%d", &n))
    {
        memset(vis, 0, sizeof vis);
        scanf("%d", &last);
        for(int i = 1; i < n; i++)
        {
            scanf("%d", &a);
            if(abs(a-last) >= n || a == last) vis[0] = 1;
            else if(vis[abs(a-last)]) vis[0] = 1;
            else vis[abs(a-last)] = 1;
            last = a;
        }
        printf(vis[0]?"Not jolly\n":"Jolly\n");
    }
    return 0;
}