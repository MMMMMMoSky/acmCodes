#include <cstdio>
#include <algorithm>
#include <cmath>
#define lowbit(x) (x&(-x))
using namespace std;

int n, m, num[100005];
long long f[100005];

int getint()
{
    int x = 0;
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
    return x;
}

void add(int x, int a)
{
    while(x <= n) f[x] += a, x += lowbit(x);
}

long long sum(int x)
{
    long long res = 0;
    while(x) res += f[x], x -= lowbit(x);
    return res;
}

int main()
{
    n = getint(), m = getint();
    for(int i = 1; i <= n; i++)
    {
        add(i, num[i]=getint());
    }
    for(int i = 1; i <= m; i++)
    {
        int t = getint();
        int a = getint();
        int b = getint();
        if(t == 1) {
            int x = getint();
            if(x == 1) continue;
            for(int j = a; j <= b; j++)
                if(num[j] >= x && !(num[j]%x)) {
                    if(!(x&(x-1))) {
                        int pow2 = log(x)/log(2);
                        add(j, (num[j]>>pow2)-num[j]);
                        num[j] >>= pow2;
                    } else {
                        add(j, num[j]/x-num[j]);
                        num[j] /= x;
                    }
                }
        } else {
            printf("%lld\n", sum(b)-sum(a-1));
        }
    }
    return 0;
}