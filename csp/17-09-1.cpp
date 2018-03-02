#include <cstdio>
#include <algorithm>
using namespace std;

int n, f[305];

int dp(int x)
{
    if(x < 0) return -(1<<25);
    if(f[x]) return f[x];
    if(x < 10) return 0;
    if(x < 20) return 1;
    if(x < 30) return 2;
    return f[x] = max(dp(x-30)+4, dp(x-50)+7);
}

int main()
{
    scanf("%d", &n);
    printf("%d\n", dp(n));
    return 0;
}