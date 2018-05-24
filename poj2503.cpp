#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char c, s[11], lens, t[11], lent;
int cnt;

struct dict {
    long long key;
    char val[11], lenv;
    dict()
    {
        lenv = 0;
    }
    bool operator < (dict k) const
    {
        return key < k.key;
    }
}dic[100005];

void getString(char *str, char &len)
{
    while(c <= 'z' && c >= 'a') {
        str[len++] = c;
        c = getchar();
    }
    c = getchar();
}

long long _hash(char *str, char &len)
{
    long long res = 0;
    for(char i = 0; i < len; i++)
        res = res*26+'z'-str[i];
    len = 0;
    return res;
}

int main()
{
    c = getchar();
    while(c != '\n')
    {
        getString(dic[cnt].val, dic[cnt].lenv);
        getString(t, lent);
        dic[cnt].key = _hash(t, lent);
        cnt++;
    }

    sort(dic, dic+cnt);
    
    while(~scanf("%s", s))
    {
        lens = strlen(s);
        long long hashs = _hash(s, lens);
        int l = 0, r = cnt-1, mid;
        while(l < r) {
            mid = (l+r)>>1;
            if(dic[mid].key < hashs) l = mid + 1;
            else r = mid;
        }
        if(dic[l].key == hashs) printf("%s\n", dic[l].val);
        else printf("eh\n");
    }
    return 0;
}