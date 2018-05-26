#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

int n, len;
char s[85];
double ans;
map <char, double> M;

int getInt(int &t)
{
    int res = 0;
    while(s[t] <= '9' && s[t] >= '0')
        res = res * 10 + s[t++] - 48;
    return max(res, 1);
}

int main()
{
    M['C'] = 12.01, M['H'] = 1.008;
    M['O'] = 16.00, M['N'] = 14.01;
    scanf("%d", &n);
    while(n--)
    {
        ans = 0.0;
        scanf("%s", s);
        len = strlen(s);
        for(int i = 0; i < len;)
            ans += M[s[i]]*getInt(++i);
        printf("%.3lf\n", ans);
    }
    return 0;
}