#include <cstdio>
#include <map>
#include <cstring>
using namespace std;

int len;
char s[25];
map <char, int> dict;

int main()
{
    dict['B'] = dict['F'] = dict['P'] = dict['V'] = 1;
    dict['C'] = dict['G'] = dict['J'] = dict['K'] = 2;
    dict['Q'] = dict['S'] = dict['X'] = dict['Z'] = 2;
    dict['D'] = dict['T'] = 3;
    dict['L'] = 4;
    dict['M'] = dict['N'] = 5;
    dict['R'] = 6;
    while(~scanf("%s", s)) {
        len = strlen(s);
        if(dict[s[0]]) printf("%d", dict[s[0]]);
        for(int i = 1; i < len; i++) {
            if(!dict[s[i]] || dict[s[i]] == dict[s[i-1]]) continue;
            printf("%d", dict[s[i]]);
        }
        putchar('\n');
    }
    return 0;
}