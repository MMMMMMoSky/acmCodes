#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int t, ans, len1, len2, f[2005][2005];
char s1[2005], s2[2005];

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        memset(f, 0, sizeof f);
        scanf("%s %s", s1, s2);
        ans = 0;
        len1 = strlen(s1);
        len2 = strlen(s2);
        for(int i = 0; i < len1; i++)
            f[i][0] = s1[i] == s2[0];
        for(int i = 0; i < len2; i++)
            f[0][i] = s1[0] == s2[i];
        for(int i = 1; i < len1; i++)
        for(int j = 1; j < len2; j++)
            f[i][j] = (s1[i] == s2[j]) ? f[i-1][j-1]+1 : 0;
        for(int i = 0; i < len1; i++)
        for(int j = 0; j < len2; j++)
            ans = max(ans, f[i][j]);
        printf("%d\n", ans);
    }
    return 0;
}