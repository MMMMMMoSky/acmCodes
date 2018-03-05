#include <cstdio>
#include <algorithm>
#define lowbit(x) (x&(-x))
using namespace std;

int n, m, num[100005], f[100005];

void add(int x, int a)
{
    while(x <= n) f[x] += a, x += lowbit(x);
}

int sum(int x)
{
    int res = 0;
    while(x) res += f[x], x -= lowbit(x);
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", num + i);
        add(i, num[i]);
    }
    for(int i = 1; i <= m; i++)
    {
        int t, a, b, x;
        scanf("%d%d%d", &t, &a, &b);
        if(t == 1) {
            scanf("%d", &x);
            for(int j = a; j <= b; j++)
                if(!(num[j]%x)) {
                    add(j, num[j]/x-num[j]);
                    num[j] /= x;
                }
        } else {
            printf("%d\n", sum(b)-sum(a-1));
        }
    }
    return 0;
}