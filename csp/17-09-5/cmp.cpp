#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, s[100005];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", s + i);
    for(int i = 1; i <= m; i++)
    {
        int t, a, b, x;
        scanf("%d%d%d", &t, &a, &b);
        if(t == 1) {
            scanf("%d", &x);
            for(int i = a; i <= b; i++)
                if(!(s[i]%x)) s[i] /= x;
        } else {
            int res = 0;
            for(int i = a; i <= b; i++)
                res += s[i];
            printf("%d\n", res);
        }
    }
    return 0;
}