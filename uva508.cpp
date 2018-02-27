#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <bitset>
using namespace std;
const int CMPFAILED = 9130122;
const int UNCMPED = 913122;

int num, aWord_len, bigDict_len[105];
char s[105];
string words[105];
bitset <105> aWord, bigDict[105];
map < char, bitset<6> > dict;
map < char, int > dict_len;

bool isAChar(char c)
{
    if(c <= 'Z' && c >= 'A') return 1;
    if(c <= '9' && c >= '0') return 1;
    if(c == '.' || c == '-') return 1;
    return c == '*';
}

bool readString(char *t)
{
    int len = 0;
    char c = getchar();
    while(!isAChar(c)) c = getchar();
    while(isAChar(c)) t[len++] = c, c = getchar();
    t[len] = 0;
    //printf("[%s]\n", t);
    return t[0] != '*';
}

void readDict()
{
    while(readString(s))
    {
        char c = s[0];
        readString(s);
        int len = strlen(s);
        dict_len[c] = len;
        for(int i = 0; i < len; i++)
            dict[c][i] = (s[i]=='-');
    }
}

void readWords()
{
    while(cin>>words[num++])
        if(words[num-1][0] == '*') break;
    num--;
}

void buildBigDict()
{
    //sort(words, words+num);
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < words[i].size(); j++)
        {
            char c = words[i][j];
            for(int k = 0; k < dict_len[c]; k++)
                bigDict[i][bigDict_len[i]++] = dict[c][k];
        }
    }
}

void bigDictTest()
{
    for(int i = 0; i < num; i++)
    {
        cout << words[i]+" ";
        for(int j = 0; j < bigDict_len[i]; j++)
            putchar(bigDict[i][j]?'-':'.');
        putchar('\n');
    }
}

int cmp(int x)
{
    int cmpLen = min(aWord_len, bigDict_len[x]);
    for(int i = 0; i < cmpLen; i++)
        if(aWord[i] != bigDict[x][i]) return CMPFAILED;
    return abs(aWord_len-bigDict_len[x]);
}

void print(int pos, char c)
{
    cout << words[pos] << c << endl;
}

void solve()
{
    while(readString(s))
    {
        aWord_len = strlen(s);
        for(int i = 0; i < aWord_len; i++)
            aWord[i] = (s[i]=='-');
        
        int status = UNCMPED, pos = -1, PRINT = 1;
        for(int i = 0; i < num; i++)
        {
            int cmpRes = cmp(i);
            if(cmpRes == CMPFAILED) continue;
            if(!cmpRes) {
                if(!status) {
                    print(pos, '!');
                    PRINT = 0;
                    break;
                } else {
                    status = cmpRes, pos = i;
                }
            } else if(cmpRes < status) {
                status = cmpRes, pos = i;
            }
        }
        if(PRINT && status != UNCMPED) print(pos, status?'?':'\0');
    }
}

int main()
{
    readDict();
    //printf("readDict()\n");
    readWords();
    //printf("readWords()\n");
    buildBigDict();
    //printf("readBigDict()\n");
    //bigDictTest();
    solve();
    return 0;
}

/*
PS F:\ACM> ./tmp > tmp.out
A --
B ..
C -.
*
ABC
*
--
*
PS F:\ACM> cat .\tmp.out
*?
*/
