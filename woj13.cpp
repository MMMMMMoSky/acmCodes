#include <cstdio>
#include <cstring>

int len, pos;
char s[105];

char _char(int x)
{
    return s[x%len];
}

int main()
{
    while(~scanf("%s", s))
    {
        len = strlen(s), pos = 0;
        for(int i = 1; i < len; i++)
        {
            if(s[i] > s[pos]) continue;
            bool flag = 1;
            for(int j = 0; j < len; j++)
            {
                if(_char(pos+j) < _char(i+j)) {
                    flag = 0; break;
                }
                if(_char(pos+j) > _char(i+j)) {
                    flag = 1; break;
                }
            }
            if(flag) pos = i;
        }
        for(int i = 0; i < len; i++) putchar(_char(pos+i));
        putchar('\n');
    }
    return 0;
}