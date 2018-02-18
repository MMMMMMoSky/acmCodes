#include <cstdio>

int main()
{
    int N; scanf("%d", &N);
    for(int i = 1; i <= N; i++)
    {
        int n, m; scanf("%d %d", &n, &m);
        if(n&1 && m&1)
             printf("Scenario #%d:\n%d.41\n\n", i, n*m);
        else printf("Scenario #%d:\n%d.00\n\n", i, n*m);
    }
    return 0;
}