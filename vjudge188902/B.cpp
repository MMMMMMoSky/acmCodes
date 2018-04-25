#include <cstdio>

int main()
{
    int n, a, b;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d %d", &a, &b);
        while(b--)
        {
            for(int i = 1; i <= a; i++)
            {
                for(int j = 1; j <= i; j++) printf("%d", i);
                printf("\n");
            }
            for(int i = a-1; i; i--)
            {
                for(int j = 1; j <= i; j++) printf("%d", i);
                printf("\n");
            }
            if(b) printf("\n");
        }
        if(n) printf("\n");
    }
    return 0;
}